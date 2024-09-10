#include "directory.hpp"

#include <sys/mount.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ftw.h>

#include "logger.hpp"
#include "exit.hpp"

using zstring = const char*;
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
        // TODO: internationalize message
        utils::Logger::error("failed to make temporary directory [%d %s]", errno, std::strerror(errno));
        return {};
    }
    
    path result = directory;
    delete[] directory;
    return result;
}

utils::exit_type utils::delete_directory(path directory){
    errno = 0;

    const auto update_permissions = [](const char *fpath, const struct stat*, int, FTW*) -> int {
        // take ownership of the file
        if(chown(fpath, getuid(), getgid())){
            // if we can not take ownership, try leaving permissions as they were
            // note: returning FTW_CONTINUE is not really needed unless FTW_ACTIONRETVAL is set
            return FTW_CONTINUE;
        }

        // change the permissions to allow read/write from owner
        if(chmod(fpath, S_IRUSR | S_IRUSR)){
            // TODO: internationalize message
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
                    // TODO: internationalize message
                    utils::Logger::error("failed to delete directory [%d %s]", errno, std::strerror(errno));
                }

                break;
            
            case FTW_D: // path is a directory
            case FTW_DP:
                // try to delete
                // fail is ok ish
                if(rmdir(fpath)){
                    // TODO: internationalize message
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
        // TODO: better return error code
        return exit::FAILURE;
    }

    // delete all files and directories (post order, ignore mounts, do not follow symlinks)
    if(nftw(directory.c_str(), delete_path, -1, FTW_DEPTH | FTW_MOUNT | FTW_PHYS)){
        // TODO: better return error code
        return exit::FAILURE;
    }

    // TODO: better return error code
    return errno ? exit::FAILURE : exit::SUCCESS;
}

utils::exit_type utils::create_overlay(path merge, path upper, path lower, path work){
    std::string payload =
        "lowerdir=" + lower.string() +
        ",upperdir=" + upper.string() + 
        ",workdir=" + work.string();

    const zstring filetype = "overlay";
    const zstring device = "overlay";

    if(mount(device, merge.c_str(), filetype, 0, payload.c_str())){
        // TODO: internationalize message
        Logger::error("failed to create overlay mount [%d %s]", errno, std::strerror(errno));
        
        // TODO: add more error returns
        if(errno == EACCES){
            return exit::INSUFFICENT_PERMISSIONS;
        }

        return exit::FAILURE;
    }

    return exit::SUCCESS;
}