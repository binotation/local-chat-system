#include "unity.h"
#include "clientlib.h"

static Args args;

void setUp( void )
{
    dynstring_init( &args.authdstr, 16 );
}

void tearDown( void )
{
    dynstring_destroy( &args.authdstr );
}

void test_parse_args4( void )
{
    char *argv[4] = { "client", "Austin", "test/testfiles/auth.txt", "20097" };
    enum ParseArgsResult res = parse_args( &args, 4, argv );
    TEST_ASSERT_EQUAL( PARSE_ARGS_SUCCESS, res );
    TEST_ASSERT_EQUAL_STRING( "Austin", args.chosen_name );
    TEST_ASSERT_EQUAL_STRING( "dcmkl 13niojhkdc juwnkxsaFG# j112df", args.authdstr.str );
    TEST_ASSERT_EQUAL_STRING( "localhost", args.host );
    TEST_ASSERT_EQUAL_STRING( "20097", args.port );
}

void test_parse_args5( void )
{
    char *argv[5] = { "client", "Patryk", "test/testfiles/auth.txt", "127.0.0.1", "6952" };
    enum ParseArgsResult res = parse_args( &args, 5, argv );
    TEST_ASSERT_EQUAL( PARSE_ARGS_SUCCESS, res );
    TEST_ASSERT_EQUAL_STRING( "Patryk", args.chosen_name );
    TEST_ASSERT_EQUAL_STRING( "dcmkl 13niojhkdc juwnkxsaFG# j112df", args.authdstr.str );
    TEST_ASSERT_EQUAL_STRING( "127.0.0.1", args.host );
    TEST_ASSERT_EQUAL_STRING( "6952", args.port );
}

void test_parse_args_authfile_not_found( void )
{
    char *argv[5] = { "client", "Patryk", "auth.txt", "192.168.1.222", "46253" };
    enum ParseArgsResult res = parse_args( &args, 5, argv );
    TEST_ASSERT_EQUAL( PARSE_ARGS_AUTHFILE_NOT_FOUND, res );
}

void test_parse_args_invalid_args_count( void )
{
    char *argv[1] = { "client" };
    enum ParseArgsResult res = parse_args( &args, 1, argv );
    TEST_ASSERT_EQUAL( PARSE_ARGS_INVALID_ARGS_COUNT, res );
}

int main( void )
{
    UNITY_BEGIN();
    RUN_TEST( test_parse_args4 );
    RUN_TEST( test_parse_args5 );
    RUN_TEST( test_parse_args_authfile_not_found );
    RUN_TEST( test_parse_args_invalid_args_count );
    return UNITY_END();
}