# Janet miniz bindings

Bindings to the miniz library in Janet. Currently exposes in memory compression only.

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
