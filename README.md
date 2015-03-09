# Freq Shift Component

This component takes an input that is either real or complex and shifts its frequency spectrum by a specified amount. The amount by which the frequency is shifted is specified by the frequency_shift property and is given in Hertz.

## Building & Installation
    ./reconf
    ./configure
    make -j
    sudo make install

## Notes

This component takes a float as input and produces a float as output. Regardless of the input, the output of the device will always be a complex vector.

## Copyrights

This work is protected by Copyright. Copyright information is included on all files within the component.

## Liscense

The Real Part Component is licensed under the Lesser GNU General Public License (LGPL).
