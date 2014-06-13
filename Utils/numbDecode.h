#pragma once
/*
* Copyright 2004 Christopher M. Bouzek
*/

namespace Utils{

	/// <summary>
	/// Utility class to do big-endian to little endian conversions and the like.
	/// This is for unsigned numbers only; use the IPAddress class for signed values.
	/// </summary>
	class UnsignedNumConverter{
	/// <summary>
	/// Do not instantiate.
	/// </summary>
	private:
		UnsignedNumConverter( ){}

		/// <summary>
		/// Converts from big-endian to little endian and vice versa.
		/// </summary>
		/// <param name="val">The value to swap.</param>
		/// <returns>The byte-swapped value, 0 if val &lt; 0</returns>

	public:
		static DWORD SwapByteOrdering( DWORD val ){
			if( val < 0 ) return 0;

		return ( ( val << 24 ) & 0xFF000000 ) + ( ( val << 8 ) & 0x00FF0000 ) +
			( ( val >> 8 ) & 0x0000FF00 ) + ( ( val >> 24 ) & 0x000000FF );
		}

		/// <summary>
		/// Converts from big-endian to little endian and vice versa. Don't use
		/// for negative integers; it has not been tested for that.
		/// </summary>
		/// <param name="val">The value to swap.</param>
		/// <returns>The byte-swapped value, 0 if val &lt; 0</returns>
		static WORD SwapByteOrdering( WORD val ){
			if( val < 0 )return 0;

			return ( WORD )( ( ( val << 8 ) & 0xFF00 ) + ( ( val >> 8 ) & 0x00FF ) );
		}
	};
}
