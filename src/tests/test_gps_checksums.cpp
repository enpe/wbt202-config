/**
  * @file test_gps_checksums.cpp
  *
  * @brief Ensures that the checksums in @c Wbt202Gps are computed correctly.
  *
  * This test requires the pathname of a (valid) GPS.BIN. The file is loaded
  * and a new instance is cloned. The checksums are computed for that second
  * instance and compared to the original ones. If the checksums are identical,
  * the test is considered as passed, otherwise as failed.
  */

#include <wbt202/wbt202.h>
#include <wbt202/utils.h>

#include <iostream>
#include <string>

bool testGpsChecksums( std::string filename )
{
	std::cout << std::endl << "file: " << filename << std::endl;

	std::vector<char> buffer = wbt202::readFile( filename.c_str() );
	if ( buffer.empty() )
		return false;

	bool passed = false;
	GpsBin * original = wbt202::toGpsBin( buffer );

	if ( original )
	{
		// Re-compute the checksums and compare them to the original.
		GpsBin test = *original;
		wbt202::setChecksum( test );

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
			{ original->cfg_sbas.footer.checksum_01, original->cfg_sbas.footer.checksum_02, test.cfg_sbas.footer.checksum_01, test.cfg_sbas.footer.checksum_02 },
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
