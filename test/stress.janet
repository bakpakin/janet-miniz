(import ../build/miniz :as miniz)

(def rng (math/rng (os/cryptorand 16)))
(def chunk-initial @"")
(def chunk-compressed @"")
(def chunk-decompressed @"")
(var good-count 0)
(def bad @[])

(loop [level :range [1 10]
       size :range [10 800010 32000]
       prefix :in ["" (string/repeat "abc" 20)]]
  (buffer/clear chunk-initial)
  (buffer/clear chunk-compressed)
  (buffer/clear chunk-decompressed)
  (buffer/push-string chunk-compressed prefix)
  (buffer/push-string chunk-decompressed prefix)
  (math/rng-buffer rng size chunk-initial)
  (miniz/compress chunk-initial level chunk-compressed)
  (miniz/decompress chunk-compressed chunk-decompressed)
  (if (deep= chunk-initial chunk-decompressed)
    (++ good-count)
    (array/push bad [(string chunk-initial) level])))

(unless (empty? bad)
  (each b bad
    (print "Bad compression!"))
  (os/exit 1))
