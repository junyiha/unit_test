#!/usr/bin/env python

import sys
import os

if os.name == 'nt':
    os.environ['PATH'] = os.path.join(os.path.dirname(__file__)) + ';' + os.environ.get('PATH', '')
    dll_path = os.path.join(os.path.dirname(__file__), '../../../bin')
    os.add_dll_directory(dll_path)
    os.environ['PATH'] = dll_path + ';' + os.environ.get('PATH', '')
else:
    os.environ['LD_LIBRARY_PATH'] = os.path.join(os.path.dirname(__file__), '../../../lib') + ':' + os.environ.get('LD_LIBRARY_PATH', '')

# this module name needs to be same with PY_MODULE_NAME defined in cmake
from py_xyz_sensor import *
