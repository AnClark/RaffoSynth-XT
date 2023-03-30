
# RaffoSynth-XT

**RaffoSynth** is a digital emulator of a minimoog synthesizer, written by [Julián Palladino](https://github.com/julianpalladino) and [Nicolas Roulet](https://github.com/nicoroulet). Originally it is built as an LV2 audio plugin for Linux.

Now RaffoSynth is implemented as a cross-platform audio plugin by AnClark Liu. To distinguish, this project is called **RaffoSynth-XT**.

## Source Tree

- `plugin`: Plugin interface.
- `src`: Synthesizer engine by Julián and Nicolas. Introduced as a submodule.
- `dpf`: DISTRHO Plugin Framework source tree. Introduced as a submodule as well.

## Documentation

Documentation can be found in `src/RaffoSynth.pdf`. This includes development explanation and experimentation (French only).

## Dependencies

The only dependency is DISTRHO Plugin Framework.

## Compile

```bash
# Clone this repo
git clone https://github.com/AnClark/RaffoSynth-XT.git --recursive
cd RaffoSynth-XT

# In case you forgot the `--recursive` switch above
git submodule update --init --recusrive

# Now let's build!
cmake -S . -B build
cmake --build build
```

Built plugins reside in `build/bin/`.

Optionally, you can also build the original LV2 plugin. Refer to `src/README.md` for more details.

## Run

RaffoSynth-XT supports those plugin formats:

- VST 2.4
- VST3
- LV2
- CLAP

Just copy plugin directories or files to your DAW's scan pathes, then re-scan plugins in your DAW.

## License

RaffoSynth-XT is licensed under GPLv3, while the original RaffoSynth is MIT-licensed.
