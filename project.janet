(declare-project
  :name "janet-miniz"
  :author "calsrose@gmail.com"
  :license "MIT")

(declare-native
  :name "miniz"
  :headers ["miniz.h"]
  :source ["entry.c" "miniz.c"])
