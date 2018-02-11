/*
    @title
        maskedkitty
    @author
        AHXR (https://github.com/AHXR)
    @copyright
        2018

    maskedkitty is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    maskedkitty is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with maskedkitty.  If not, see <http://www.gnu.org/licenses/>.
*/
//=======================================================
#ifndef     FILE_PUMP_H
#define     FILE_PUMP_H

#include    <sys/stat.h>

#define     SIZE_KB 0
#define     SIZE_MB 1
#define     SIZE_GB 2

#define     MAX_FILE_SIZES 3

#define     updateEstimate( a ) { \
    generateEstimation( c_tmp, qs_file_path.qstr_char, qs_pump.qstr_char, a ); \
        ui->lblFileInfo->setText( c_tmp ); \
}

unsigned long getFileSize( const char * path );
unsigned long long calculateSize( const unsigned short code, unsigned long currentsize, unsigned short addition );
unsigned short searchFileSizeIndex( const char * text );
long long generateEstimation( char * output, const char * path, const char * type, unsigned int addition );

char fileSizes[ MAX_FILE_SIZES ][ 30 ] = {
    "KBs (Kilobytes)",
    "MBs (Megabytes)",
    "GBs (Gigabytes)"
};

unsigned long getFileSize( const char * path ) {
    struct stat st_tmp;
    return ( stat( path, &st_tmp ) == 0 ) ? st_tmp.st_size : 0; // If the file exist, then return the size, otherwise 0
}

unsigned short searchFileSizeIndex( const char * text ) {
    for( unsigned short us = 0; us < MAX_FILE_SIZES; us ++ )
        if( !strcmp( text, fileSizes[ us ] ) )
            return us;

    return -1;
}

unsigned long long calculateSize( const unsigned short code, unsigned long long currentsize, unsigned short addition ) {
    switch( code ) {
        case SIZE_KB: {
            return currentsize + ( addition * 1024 );
        }
        case SIZE_MB: {
            return currentsize + ( addition * 1048576 );
        }
        case SIZE_GB: {
            return currentsize + ( addition * 1099511627776 );
        }
    }
    return 0;
}

long long generateEstimation( char * str, const char * path, const char * type, unsigned int addition ) {
    unsigned long long l_calc;
    unsigned long long l_file_size = getFileSize( path );

    switch( searchFileSizeIndex( type ) ) {
        case 0: { // KB
            l_calc = calculateSize( SIZE_KB, l_file_size, addition );
            break;
        }
        case 1: { // MB
            l_calc = calculateSize( SIZE_MB, l_file_size, addition );
            break;
        }
        case 2: { // GB
            l_calc = calculateSize( SIZE_GB, l_file_size, addition );
            break;
        }
    }

    sprintf( str, "<html><head/><body><p>The file you currently have open has a file size of %llu bytes. After strictly file pumping by %i %s', your file will be %llu bytes</p></body></html>", l_file_size, addition, type, l_calc );
    return l_calc;
}

#endif // FILE_PUMP_H
