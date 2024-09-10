#include "directory.hpp"

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ftw.h>

#include "logger.hpp"

using utils::path;

std::optional<path> utils::create_temporary_directory(path base){
    // create directory template in the format wanted by mkdtemp
    base.append("aspm.XXXXXX");
    std::string templatestring = base.string();

    // avoid undefined behavior
    //  - const_cast<char*>(templatestring.c_str()) would probably work but is undefined
    char *directory = new char[templatestring.size() + 1];
    strcpy(directory, templatestring.c_str());

    if(mkdtemp(directory) == NULL){
        utils::Logger::error("failed to make temporary directory [%d %s]", errno, std::strerror(errno));
        return {};
    }
    
    path result = directory;
    delete[] directory;
    return result;
}

int utils::delete_directory(path directory){
    const auto update_permissions = [](const char *fpath, const struct stat*, int, FTW*) -> int {
        // take ownership of the file
        if(chown(fpath, getuid(), getgid())){
            // if we can not take ownership, try leaving permissions as they were
            // note: returning FTW_CONTINUE is not really needed unless FTW_ACTIONRETVAL is set
            return FTW_CONTINUE;
        }

        // change the permissions to allow read/write from owner
        if(chmod(fpath, S_IRUSR | S_IRUSR)){
            utils::Logger::error("failed to change permissions [%d %s]", errno, std::strerror(errno));
        }

        // note: returning FTW_CONTINUE is not really needed unless FTW_ACTIONRETVAL is set
        return FTW_CONTINUE;
    };

    const auto delete_path = [](const char *fpath, const struct stat*, int typeflag, FTW*) -> int {
        // delete the path
        switch(typeflag){
            case FTW_F: // path is a file
                // try to delete
                // fail is ok ish
                if(unlink(fpath)){
                    utils::Logger::error("failed to delete directory [%d %s]", errno, std::strerror(errno));
                }

                break;
            
            case FTW_D: // path is a directory
            case FTW_DP:
                // try to delete
                // fail is ok ish
                if(rmdir(fpath)){
                    utils::Logger::error("failed to delete file [%d %s]", errno, std::strerror(errno));
                }

                break;
        }

        // note: returning FTW_CONTINUE is not really needed unless FTW_ACTIONRETVAL is set
        // but I need to return something anyways so why not
        return FTW_CONTINUE;
    };

    // update all permissions (pre order, ignore mounts, do not follow symlinks)
    if(nftw(directory.c_str(), update_permissions, -1, FTW_MOUNT | FTW_PHYS)){
        return -1;
    }

    // delete all files and directories (post order, ignore mounts, do not follow symlinks)
    if(nftw(directory.c_str(), delete_path, -1, FTW_DEPTH | FTW_MOUNT | FTW_PHYS)){
        return -1;
    }

    return errno ? -1 : 0;
}