// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Topologically sorts an FST.

#include <cstring>

#include <memory>
#include <string>

#include <fst/flags.h>
#include <fst/log.h>
#include <fst/script/topsort.h>

int fsttopsort_main(int argc, char **argv) {
  namespace s = fst::script;
  using fst::script::MutableFstClass;

  string usage = "Topologically sorts an FST.\n\n  Usage: ";
  usage += argv[0];
  usage += " [in.fst [out.fst]]\n";

  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(usage.c_str(), &argc, &argv, true);
  if (argc > 3) {
    ShowUsage();
    return 1;
  }

  const string in_name = argc > 1 && strcmp(argv[1], "-") != 0 ? argv[1] : "";
  const string out_name = argc > 2 ? argv[2] : "";

  std::unique_ptr<MutableFstClass> fst(MutableFstClass::Read(in_name, true));
  if (!fst) return 1;

  bool acyclic = TopSort(fst.get());

  if (!acyclic) FST_LOG(WARNING) << argv[0] << ": Input FST is cyclic";

  return !fst->Write(out_name);
}
