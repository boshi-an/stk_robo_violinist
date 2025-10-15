#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "MyBowed.h"
#include "SKINImsg.h"
#include "FileWvOut.h"

namespace py = pybind11;
using namespace stk;

// Helper: render N samples to a numpy array (mono)
static py::array_t<float> render_samples(MyBowed &inst, int num_samples)
{
  if (num_samples < 0) num_samples = 0;
  auto array = py::array_t<float>(num_samples);
  auto buf = array.mutable_unchecked<1>();
  for (int i = 0; i < num_samples; ++i) {
    buf(i) = static_cast<float>(inst.tick());
  }
  return array;
}

PYBIND11_MODULE(mybowed_py, m) {
  m.doc() = "Python bindings for MyBowed (STK-based bowed string)";

  py::class_<MyBowed>(m, "MyBowed")
    .def(py::init<StkFloat>(), py::arg("lowest_frequency") = 20.0)
    .def("set_sample_rate", &MyBowed::setSampleRate)
    .def("set_frequency", &MyBowed::setFrequency)
    .def("start_bowing", &MyBowed::startBowing, py::arg("amplitude"), py::arg("rate"))
    .def("stop_bowing", &MyBowed::stopBowing, py::arg("rate"))
    .def("control_change", &MyBowed::controlChange, py::arg("number"), py::arg("value"))
    .def("tick", [](MyBowed &self){ return static_cast<float>(self.tick()); })
    .def("render", &render_samples, py::arg("num_samples"))
  ;

  // Expose control constants on the module for convenience
  m.attr("MB_REVERB_T60") = py::int_(MyBowed::MB_ReverbT60);
  m.attr("MB_REVERB_MIX") = py::int_(MyBowed::MB_ReverbMix);

  // Expose Bowed base-class control constants (from SKINImsg.h)
  m.attr("SK_BOW_PRESSURE")       = py::int_(__SK_BowPressure_);
  m.attr("SK_BOW_POSITION")       = py::int_(__SK_BowPosition_);
  m.attr("SK_BOW_VELOCITY")       = py::int_(100);
  m.attr("SK_BASE_FREQUENCY")      = py::int_(101);
}
