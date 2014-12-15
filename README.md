# UI macros 4 KSP

An example of usage of the [macros4ksp](https://github.com/raffadrummer/macros4ksp) approach aimed at simplifying the
creeation of simple UI with the "[Kontakt](http://www.native-instruments.com/en/products/komplete/samplers/kontakt-5/) Scripting Language"

The purpose of these UI macros is to simplify the process of creating (standard) UI controls; such process usually involves various steps:

- **declare** a variable that represents the control,
- **position** the control on the *performance view*,
- **size** the control,
- **initialize** it with default values.

Thanks to the macros defined in `ui_macros.h` such steps can be perfoemd invoking a *single macro* with a suitable set of parameters.

For example, invoking the macro:

    LABEL( CTRL, X, Y, W, H, TEXT )

generates the following code:

    declare ui_label CTRL ( W, H )
    move_control_px( CTRL, UI_BORDER_LEFT + ( ( ( X ) - 1 ) ) * $UI_COL_WIDTH, UI_BORDER_TOP + ( ( ( Y ) - 1 ) ) * $UI_ROW_WIDTH )
    set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_WIDTH, ( W ) * $UI_COL_WIDTH - 2 * ( UI_PADDING_PX ) )
    set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_HEIGHT, ( H ) * $UI_ROW_WIDTH - 2 * ( UI_PADDING_PX ) )
    set_text( CTRL, TEXT )

where the first line corresponds to the variable declaration, the second line to the control positioning, the following two lines to the sizing and the last one to the initialization of the label with the given text.

## Virtual rows and columns

To understand the genral form of these UI macros the first thing to specify is how position and size can be specified.

In KSP the *performance view* "coordinates" can be specified in two different ways, using:

- rows and columns,
- pixels.

The first way is easier, but more constrained (the number of rows and columns is fixed and, moreover, such coordinates do not allow to cover all the available space); the second way is more powerful, but not so easy to use (one has to manually compute the size of various controls, for instance, to get the right position and size).

These macros try to get the best of both approaces: internally they address the space using pixels, but the user can specify positions and sizes using "virutal" rows and columns. By "virtual" is meant that the the user can decide the number of rows and columns in which the view space will be divided; of course, the larger the number of rows (or columns) the smaller they get.

## Other macro parameters

Beside the positions and sizes (that have to be specified in terms of virtual rows and columns, as explained above), the macros accept other parameters such as:

- `CTRL` the name of the variable representing the control,
- `X` the horizontal (column) position of the control,
- `Y` the vertical (row) position of the control,
- `W` the width (in columns) for the control size,
- `H` the height (in columns) for the control size,
- `TEXT` the text shown on the control,
- `DEFAULT` the default value of the control,
- `MIN` the minimum value of the control,
- `MAX` the maximum value of the control,
- `ENTRIES` the entries of the menu control,
- `FOLDER` the base folder for the file selector control,
- `COLS` the number of columns for the table control,
- `STEP` the number of steps for the value edit control,

for a more detalied list of the parameters used by the various macros refer to the `ui_macros.h` file itself.

Presently the macros don't cover all the UI controls provided by KSP, but are limited to the following ones:

    BUTTON( CTRL, X, Y, W, H, TEXT )
    LABEL( CTRL, X, Y, W, H, TEXT )
    MENU( CTRL, X, Y, W, H, ENTRIES, DEFAULT )
    MIDI_FILE_SELECTOR( CTRL, X, Y, W, H, CW, FOLDER )
    SLIDER( CTRL, X, Y, MIN, MAX, DEFAULT )
    TABLE( CTRL, X, Y, W, H, COLS, MAX )
    VALUE_EDIT( CTRL, X, Y, W, H, MIN, MAX, STEP, DEFAULT, TEXT )

Moreover some other macros are provided:

    SET_UI_HEIGHT( ROWS )
    SET_BG_IMAGE( NAME )
    HIDE_CONTROL( CTRL )
    SHOW_CONTROL( CTRL )
    MOVE_CONTROL( CTRL, X, Y )
    SIZE_CONTROL( CTRL, W, H )

## A worked out example

In the `example` directory you can find a proof of concept of the use of the macros. The code in `ui_i.ksp` builds the following UI

![screenshot](/example/screenshot.png?raw=true "screenshot")

using the macros.

The code in `model_i.ksp` contains the callbacks that react to the various control in the UI, what the callbacks do is basically to emit some text in the `OUTPUT` label.

To build the example, refer to the instructions given in the [macros4ksp](https://github.com/raffadrummer/macros4ksp) repository.


![Analytics](https://ga-beacon.appspot.com/UA-49277456-5/uimacros4ksp?pixel)
