
#include <wbt202/wbt202.h>
#include <wbt202/wbt202_utils.h>

#include <iostream>
#include <string>

bool testGpsChecksums( std::string path )
{
	std::string filename = path + "/GPS.BIN";
	std::cout << std::endl << "file: " << filename << std::endl;

	std::vector<char> buffer = readFile( filename.c_str() );
	if ( buffer.empty() )
		return false;

	bool passed = false;
	Wbt202Gps * original = toWbt202Gps( buffer );

	if ( original )
	{
		// Re-compute the checksums and compare them to the original.
		Wbt202Gps test = *original;
		setChecksum( test );

		struct Field
		{
			uint8_t oldChecksum_01;
			uint8_t oldChecksum_02;

			uint8_t newChecksum_01;
			uint8_t newChecksum_02;
		};

		Field field[] =
		{
			{ original->block_16.footer.checksum_01, original->block_16.footer.checksum_02, test.block_16.footer.checksum_01, test.block_16.footer.checksum_02 },
			{ original->block_26.footer.checksum_01, original->block_26.footer.checksum_02, test.block_26.footer.checksum_01, test.block_26.footer.checksum_02 },
			{ original->block_36.footer.checksum_01, original->block_36.footer.checksum_02, test.block_36.footer.checksum_01, test.block_36.footer.checksum_02 },
			{ original->block_46.footer.checksum_01, original->block_46.footer.checksum_02, test.block_46.footer.checksum_01, test.block_46.footer.checksum_02 },
			{ original->block_76.footer.checksum_01, original->block_76.footer.checksum_02, test.block_76.footer.checksum_01, test.block_76.footer.checksum_02 },
			{ original->block_A2.footer.checksum_01, original->block_A2.footer.checksum_02, test.block_A2.footer.checksum_01, test.block_A2.footer.checksum_02 },
			{ original->block_BE.footer.checksum_01, original->block_BE.footer.checksum_02, test.block_BE.footer.checksum_01, test.block_BE.footer.checksum_02 },
		};

		int count = 0;
		bool isIdentical = true;
		for ( int i = 0; i < count; ++i )
		{
			if (
				field[i].oldChecksum_01 != field[i].newChecksum_01 ||
				field[i].oldChecksum_02 != field[i].newChecksum_02 )
			{
				isIdentical = false;
				break;
			}
		}

		if ( isIdentical )
			passed = true;
	}

	delete original;

	return passed;
}

int main( int argc, char ** argv )
{
	if ( argc <= 1 )
		return 1;

	return ( testGpsChecksums( argv[1] ) ? 0 : 1 );
}
