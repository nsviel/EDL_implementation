#ifndef TEXT_EDITOR_THEME_H
#define TEXT_EDITOR_THEME_H


const TextEditor::Palette & TextEditor::get_custom_palette(){
	const static Palette p = { {
			0xff7f7f7f,	// Default
			0xffC586C0,	// Keyword
			0xffB5CEA8,	// Number
			0xff6ad169,	// String - vert
			0xffCE9178, // Char literal
			0xffD4D4D4, // Punctuation
			0xffC586C0,	// Preprocessor
			0xffffffff, // Identifier
			0xffffffff, // Known identifier
			0xff5179b5, // Preproc identifier
			0xffa3a3a3, // Comment (single line)
			0xffa3a3a3, // Comment (multi line)
			0xff151515, // Background	- black
			0xff222222, // Cursor
			0xff264F78, // Selection
			0x80F44747, // ErrorMarker
			0x40f08000, // Breakpoint
			0xff5A5A5A, // Line number
			0x40404040, // Current line fill - grey
			0x40808080, // Current line fill (inactive)
			0x40a0a0a0, // Current line edge
		} };
	return p;
}

#endif
