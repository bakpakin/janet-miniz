(declare-project
  :name "janet-miniz"
  :description "Janet bindings to the miniz library."
  :author "calsrose@gmail.com"
  :url "https://github.com/bakpakin/janet-miniz"
  :license "MIT")

(declare-native
  :name "miniz"
  :headers ["miniz.h"]
  :source ["entry.c" "miniz.c"])
