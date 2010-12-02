# $Id: version.py 148 2006-09-22 01:30:23Z quarl $

import subprocess

def pipefrom(cmd):
    return subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]

# TODO: get this from config file or vice versa, but don't hard-code both.
version = '1.1.0'
