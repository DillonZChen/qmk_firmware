My config [here](https://github.com/DillonZChen/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/DillonZChen/keymap.c)

Default config [here](https://github.com/DillonZChen/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/default/keymap.c)

Instructions

    python3 -m pip install --user qmk
    echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc
    qmk setup DillonZChen/qmk_firmware
    qmk config user.keyboard=keebio/iris/rev8
    qmk config user.keymap=DillonZChen
    qmk compile
    qmk flash

## Lily58 with Helios controllers

The custom Lily58 keymap is located at:

```text
keyboards/lily58/keymaps/DillonZChen/keymap.c
```

Controller and split-handedness settings are in the same directory:

- `config.h` enables persistent per-half handedness so either half can be connected by USB.
- `rules.mk` selects the RP2040-based Helios controller.

### Rebuild after changing the layout

From the QMK repository root, run:

```bash
qmk clean
qmk compile -kb lily58/rev1 -km DillonZChen
```

The resulting shared firmware is:

```text
lily58_rev1_DillonZChen_helios.uf2
```

### Flash a normal layout update

Flash the shared UF2 onto both halves so either half can act as the USB master:

1. Disconnect USB, then disconnect TRRS. Never connect or disconnect TRRS while the keyboard is powered.
2. Connect one half directly by USB and double-press its Reset button.
3. Wait for the `RPI-RP2` USB drive to appear.
4. Copy the firmware to it:

   ```bash
   cp lily58_rev1_DillonZChen_helios.uf2 /media/$USER/RPI-RP2/
   ```

5. Wait for `RPI-RP2` to disappear, then disconnect USB.
6. Repeat the same process and use the same UF2 for the other half.
7. Disconnect USB, reconnect TRRS, and then connect USB to either half.

### Initialize or repair left/right handedness

This is only necessary for a new controller or if its stored handedness has been erased. Keep the halves disconnected from one another and run the matching command before resetting that controller.

For the left controller:

```bash
qmk flash -kb lily58/rev1 -km DillonZChen -bl uf2-split-left
```

For the right controller:

```bash
qmk flash -kb lily58/rev1 -km DillonZChen -bl uf2-split-right
```

When each command waits for a bootloader, double-press Reset on the corresponding controller. After both sides have been initialized, future keymap updates use the same shared UF2 on both halves.

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
