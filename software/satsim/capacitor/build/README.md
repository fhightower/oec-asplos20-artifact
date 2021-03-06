# Compilation and Testing

Compilation is managed by CMake to facilitate straightforward compilation on
multiple platforms. Ensure that CMake is installed before proceeding. A
CMakeLists.txt file should be available in the test directory.

## Compile

Execute the following commands.

```bash
cd $HOME/git-repos/oec-asplos20-artifact/software/satsim/capacitor/build/
cmake ../test/
make
```

## Run

After compilation, run the executable.

```bash
./test_capacitor
```

## License

Written by Bradley Denby  
Other contributors: None

To the extent possible under law, the author(s) have dedicated all copyright and
related and neighboring rights to this work to the public domain worldwide. This
work is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication with this
work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.
