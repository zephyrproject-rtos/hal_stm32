import os
import sys

import pytest


_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(_SCRIPT_DIR, "..", "..", "genpinctrl"))


@pytest.fixture()
def data():
    """Pytest fixture to load test data files"""
    return os.path.join(_SCRIPT_DIR, "data")


@pytest.fixture()
def cubemx(data):
    """Pytest fixture to load test CubeMX files"""
    return os.path.join(data, "cubemx")
