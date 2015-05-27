#ifndef PY_BEHAVIOR_H
#define PY_BEHAVIOR_H

#include <string>
#include <Behavior.h>
#include "Helper.h"
#ifdef NO_TR1
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>

// forward declare PyObject
// as suggested on the python mailing list
// http://mail.python.org/pipermail/python-dev/2003-August/037601.html
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

namespace behavior_learning { namespace bl_loader {

class PyBehavior : public behavior_learning::Behavior {
public:
  ~PyBehavior();

  // this is the prefered way of construction
  static PyBehavior* fromPyObject(PyObject *pObj);

  void setInputs(const double *values, int numInputs);
  void getOutputs(double *values, int numOutputs) const;

  /**
   * Meta-parameters could be the goal, obstacles, etc.
   * Each parameter is a list of doubles identified by a key.
   */
#ifdef NO_TR1
  typedef std::unordered_map<std::string, std::vector<double> > MetaParameters;
#else
  typedef std::tr1::unordered_map<std::string, std::vector<double> > MetaParameters;
#endif
  void setMetaParameters(const MetaParameters &params);

  void step();
  bool canStep() const;

protected:
  // should only be called by fromPyObject
  PyBehavior(int numInputs, int numOutputs);

private:
  // disallow copying and assigning
  PyBehavior(const PyBehavior&);
  PyBehavior& operator=(const PyBehavior&);

  PyObjectPtr py_behavior;
  py_callable_info_t set_inputs;
  py_callable_info_t get_outputs;

}; /* end of class PyBehavior */

}}

#endif /* PY_BEHAVIOR_H */
