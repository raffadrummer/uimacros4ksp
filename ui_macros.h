{/***

	This module contains a set of macros to simplify the definition of a UI
	based on standard Kontakt controls.

	Given the dimensions in pixel of the available area, here one can define a
	number of *virtual* rows and columns (whose dimnesion will be computed
	according to the available area) that will henceforth be used to
	*position* and *size* controls. Rows and columns are numbered from 1
	onwards.

*/}

{/*

	The following values can be defined before including this file to set the
	number of virtual rows and columns. Reasonable value range from …; the
	last value defines the "padding" that will be placed around every control
	in a  cell (defined as the intersection of a row and a column). If not
	defined externally, a default of 24 rows and 12 columns, with a 2px
	padding, will be set here.

	Observe that if the number of rows is different from 24 or the padding is
	different from 2, then the default backround image for some controls (such
	as buttons) being of fixed size will appear not to fit exatly the control.

*/}

#ifndef UI_NUM_ROWS
#define UI_NUM_ROWS 24
#endif

#ifndef UI_NUM_COLS
#define UI_NUM_COLS 12
#endif

#ifndef UI_PADDING_PX
#define UI_PADDING_PX 2
#endif


{/* The following part of this file **sould not be modified**. */}

{/*
	The following values are **fixed** by the current release of Kontakt
*/}

#define UI_WIDTH 632
#define UI_HEIGHT 540
#define UI_BORDER_LEFT 66
#define UI_BORDER_RIGHT 16
#define UI_BORDER_TOP 10
#define UI_BORDER_BOTTOM 2

{/* The computed size of a virtual row/column */}

declare const $UI_ROW_WIDTH := ( ( UI_HEIGHT - UI_BORDER_TOP - UI_BORDER_BOTTOM ) / UI_NUM_ROWS ) {/* altezza in px di una riga */}
declare const $UI_COL_WIDTH := ( ( UI_WIDTH - UI_BORDER_LEFT - UI_BORDER_RIGHT ) / UI_NUM_COLS ) {/* larghezza in px di una colonna */}

{/* Defines the height, in rows, of the UI. */}

#define SET_UI_HEIGHT( ROWS ) set_ui_height_px( ( ROWS ) * $UI_ROW_WIDTH )

{/* Puts a label with a background image of given NAME (relative to the resource folder). */}

#define SET_BG_IMAGE( NAME ) \
	declare ui_label $_UI_BG ( 0, 0 ) @@@\
    set_control_par_str( get_ui_id( $_UI_BG ), $CONTROL_PAR_TEXT, "" ) @@@\
    set_control_par_str( get_ui_id( $_UI_BG ), $CONTROL_PAR_PICTURE, NAME ) @@@\
    set_control_par( get_ui_id( $_UI_BG ), $CONTROL_PAR_POS_X, 0 ) @@@\
    set_control_par( get_ui_id( $_UI_BG ), $CONTROL_PAR_POS_Y, 0 )

{/*

	In all the following macros the parameter must be undestood as:

	- CTRL the name of the variable representing the control,
	- X the horizontal (column) position of the control,
	- Y the vertical (row) position of the control,
	- W the width (in columns) for the control size,
	- H the height (in columns) for the control size,
	- TEXT the text shown on the control,
	- DEFAULT the default value of the control,
	- MIN the minimum value of the control,
	- MAX the maximum value of the control,
	- ENTRIES the entries of the menu control,
	- FOLDER the base folder for the file selector control,
	- COLS the number of columns for the table control,
	- STEP the number of steps for the value edit control,

*/}


{/* Hides the CTRL control. */}

#define HIDE_CONTROL( CTRL ) hide_part( CTRL, $HIDE_WHOLE_CONTROL )

{/* Shows the CTRL control. */}

#define SHOW_CONTROL( CTRL ) hide_part( CTRL, $HIDE_PART_NOTHING )

{/* Moves the control CTRL at column X and row Y. */}

#define MOVE_CONTROL( CTRL, X, Y ) \
	move_control_px( CTRL, UI_BORDER_LEFT + ( ( ( X ) - 1 ) ) * $UI_COL_WIDTH, UI_BORDER_TOP + ( ( ( Y ) - 1 ) ) * $UI_ROW_WIDTH )

{/* Sizes the control CTRL to width W columns and height H rows. */}

#define SIZE_CONTROL( CTRL, W, H ) \
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_WIDTH, ( W ) * $UI_COL_WIDTH - 2 * ( UI_PADDING_PX ) ) @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_HEIGHT, ( H ) * $UI_ROW_WIDTH - 2 * ( UI_PADDING_PX ) )

{/* Button. */}

#define BUTTON( CTRL, X, Y, W, H, TEXT ) \
	declare ui_button CTRL @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H ) @@@\
	set_text( CTRL, TEXT )

{/* Label. */}

#define LABEL( CTRL, X, Y, W, H, TEXT ) \
	declare ui_label CTRL ( W, H ) {/* needs H lines otherwise add_text_line will not work */} @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H ) @@@\
	set_text( CTRL, TEXT )

{/* Menu. */}

	declare $_menu_entries_idx

#define MENU( CTRL, X, Y, W, H, ENTRIES, DEFAULT ) \
	declare ui_menu CTRL @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H ) @@@\
	$_menu_entries_idx := 0 @@@\
	while ( $_menu_entries_idx < num_elements( ENTRIES ) ) @@@\
		add_menu_item( CTRL, ENTRIES[ $_menu_entries_idx ], $_menu_entries_idx ) @@@\
		inc( $_menu_entries_idx ) @@@\
	end while @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_VALUE, DEFAULT )

{/* File selector for midi files. */}

#define MIDI_FILE_SELECTOR( CTRL, X, Y, W, H, CW, FOLDER ) \
	declare ui_file_selector CTRL @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H ) @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_FILE_TYPE, $NI_FILE_TYPE_MIDI ) @@@\
	set_control_par_str( get_ui_id( CTRL ), $CONTROL_PAR_BASEPATH, FOLDER ) @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_COLUMN_WIDTH, ( CW ) * $UI_COL_WIDTH )

{/* Value edit. */}

#define VALUE_EDIT( CTRL, X, Y, W, H, MIN, MAX, STEP, DEFAULT, TEXT ) \
	declare ui_value_edit CTRL ( MIN, MAX, STEP ) @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H ) @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_VALUE, DEFAULT ) @@@\
	set_text( CTRL, TEXT )

{/* Slider. */}

#define SLIDER( CTRL, X, Y, MIN, MAX, DEFAULT ) \
	declare ui_slider CTRL ( MIN, MAX ) @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	set_control_par( get_ui_id( CTRL ), $CONTROL_PAR_VALUE, DEFAULT )

{/* Table. */}

#define TABLE( CTRL, X, Y, W, H, COLS, MAX ) \
	declare ui_table CTRL[ COLS ] ( W, H, MAX ) @@@\
	MOVE_CONTROL( CTRL, X, Y ) @@@\
	SIZE_CONTROL( CTRL, W, H )
