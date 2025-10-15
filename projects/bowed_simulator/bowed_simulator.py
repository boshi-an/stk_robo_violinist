"""
Typed Python wrapper for the mybowed_py extension.

Importing this module provides type hints so linters/IDEs know the
available methods and their signatures, while delegating to the
native extension at runtime.
"""

from __future__ import annotations

import os
import sys
from typing import TYPE_CHECKING

try:
    # Try normal import first (installed or on PYTHONPATH)
    import mybowed_py as _mb
except Exception:
    # Fallback: search common local build locations
    _HERE = os.path.dirname(os.path.abspath(__file__))
    candidates = [
        _HERE,
        os.path.abspath(os.path.join(_HERE, "..", "bowed_simulator", "lib")),
    ]
    for p in candidates:
        if p not in sys.path:
            sys.path.insert(0, p)
    import mybowed_py as _mb  # type: ignore


# Type stubs for linters/IDEs
if TYPE_CHECKING:
    import numpy as np

    class MyBowed:
        def __init__(self, lowest_frequency: float = 20.0) -> None: ...
        def set_sample_rate(self, sample_rate: float) -> None: ...
        def set_frequency(self, frequency: float) -> None: ...
        def start_bowing(self, amplitude: float, rate: float) -> None: ...
        def stop_bowing(self, rate: float) -> None: ...
        def control_change(self, number: int, value: float) -> None: ...
        def tick(self) -> float: ...
        def render(self, num_samples: int) -> "np.ndarray": ...

else:
    # Runtime bindings
    MyBowed = _mb.MyBowed  # type: ignore[attr-defined]


__all__ = [
    "MyBowed",
]
