#!/usr/bin/env python
"""Configure the build.

- Fetch HDF5 headers.
- Create libconfig.h
- Create defines.mk

This is not used by './unittest/'.
"""
import commands
import contextlib
import os
import sys

def log(msg):
    sys.stderr.write(msg)
    sys.stderr.write('\n')

def shell(cmd):
    log(cmd)
    status, output = commands.getstatusoutput(cmd)
    if status:
        raise Exception('%d <- %r' %(status, cmd))
    return output

def update(fn, content):
    current_content = open(fn).read() if os.path.exists(fn) else None
    if content != current_content:
        log('writing to %r' %fn)
        log('"""\n' + content + '"""')
        open(fn, 'w').write(content)

def compose_libconfig(pbbam=False):
    if pbbam:
        content = """
#define USE_PBBAM
"""
    else:
        content = """
"""
    return content

def compose_defines_with_hdf_headers(HDF_HEADERS):
    return """
HDF_HEADERS:=%(HDF_HEADERS)s
#HDF5_INC?=${HDF_HEADERS}/src
INCLUDES+=-I${HDF_HEADERS}/src -I${HDF_HEADERS}/c++/src
INCLUDES+=-I../pbdata -I../hdf -I../alignment
"""%(dict(HDF_HEADERS=HDF_HEADERS))

def compose_defines():
    """
    Note that our local 'hdf' subdir will not even build
    in this case.
    """
    return """
nohdf:=1
INCLUDES+=-I../pbdata -I../hdf -I../alignment
"""

@contextlib.contextmanager
def cd(nwd):
    cwd = os.getcwd()
    log('cd %r -> %r' %(cwd, nwd))
    os.chdir(nwd)
    yield
    os.chdir(cwd)
    log('cd %r <- %r' %(cwd, nwd))

def fetch_hdf5_headers():
    """Fetch into ./hdf/HEADERS directory.
    Return actual directory path, relative to subdirs.
    """
    version = 'hdf5-1.8.12-headers'
    if not os.path.isdir(os.path.join('hdf', version)):
        with cd('hdf'):
            cmd = 'curl -k -L https://www.dropbox.com/s/8971bcyy5o42rxb/hdf5-1.8.12-headers.tar.bz2\?dl\=0 | tar xjf -'
            shell(cmd)
    return os.path.join('../hdf', version) # Relative path might help caching.

def configure_nopbbam():
    HDF_HEADERS = fetch_hdf5_headers()
    content = compose_defines_with_hdf_headers(HDF_HEADERS)
    update('defines.mk', content)
    content = compose_libconfig(pbbam=False)
    update('pbdata/libconfig.h', content)

def configure_nopbbam_nohdf5():
    content = compose_defines()
    update('defines.mk', content)
    content = compose_libconfig(pbbam=False)
    update('pbdata/libconfig.h', content)

def main():
    """We are still deciding what env-vars to use, if any.
    """
    if 'NOPBBAM' in os.environ:
        if 'NOHDF' in os.environ:
            configure_nopbbam_nohdf5()
        else:
            configure_nopbbam()
    else:
        log('not ready for pacbio internal yet')


if __name__=="__main__":
    main()
