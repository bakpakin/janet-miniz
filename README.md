# Janet miniz bindings

Bindings to the [miniz](https://github.com/richgel999/miniz) library in Janet. Currently
exposes in memory compression only.

## Install

    [sudo] jpm install miniz

## Documentation

HTML Documentation can be generated locally with mendoza.

```
[sudo] jpm install mendoza
mdz build
mdz serve
```

### Functions

- `(miniz/compress bytes &opt level buffer)`
- `(miniz/decompress &opt buffer)`
