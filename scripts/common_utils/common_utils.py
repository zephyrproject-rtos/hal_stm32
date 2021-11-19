import subprocess
import os
import stat
from pathlib import Path
import logging


def apply_patch(patch_file, dest_path):
    """Apply patch and report error if any"""
    cmd = (
        "git",
        "apply",
        "--recount",
        "--reject",
        patch_file,
    )
    log_path = dest_path / str(Path(patch_file).name + ".log")
    with open(log_path, "w") as output_log:
        if subprocess.call(cmd, stderr=output_log, cwd=dest_path):
            logging.error(
                "##########################  "
                + "ERROR when applying patch to zephyr: "
                + "###########################\n"
                + f"           see {str(log_path)}\n"
                + f"patch file:{patch_file}"
            )

            # Print list of conflicting file
            conflict = "Potential merge conflict:\n"

            with open(str(log_path), "r", encoding="utf8", errors="ignore") as f:
                # ignore lines with non UTF-8 characters
                previous_conflict_file = ""
                for line in f:
                    if line.startswith("error: patch failed:"):
                        conflict_file = line.split(":")[2]
                        if conflict_file != previous_conflict_file:
                            previous_conflict_file = conflict_file
                            conflict = f"{conflict}               {conflict_file}\n"
            logging.error(conflict)


def remove_readonly(func, path, _):
    """Remove read only protection"""
    os.chmod(path, stat.S_IWRITE)
    func(path)
