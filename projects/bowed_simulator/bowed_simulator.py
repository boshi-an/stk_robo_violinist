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

    # Control constants exposed by the native module
    MB_REVERB_T60: int = _mb.MB_REVERB_T60  # type: ignore[attr-defined]
    MB_REVERB_MIX: int = _mb.MB_REVERB_MIX  # type: ignore[attr-defined]

    SK_BOW_PRESSURE: int = _mb.SK_BOW_PRESSURE  # type: ignore[attr-defined]
    SK_BOW_POSITION: int = _mb.SK_BOW_POSITION  # type: ignore[attr-defined]
    SK_BOW_VELOCITY: int = _mb.SK_BOW_VELOCITY  # type: ignore[attr-defined]
    SK_BASE_FREQUENCY: int = _mb.SK_BASE_FREQUENCY  # type: ignore[attr-defined]

__all__ = [
    "MyBowed",
    "MB_REVERB_T60",
    "MB_REVERB_MIX",
    "SK_BOW_PRESSURE",
    "SK_BOW_POSITION",
    "SK_BOW_VELOCITY",
    "SK_BASE_FREQUENCY",
]
