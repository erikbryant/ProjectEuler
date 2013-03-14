#include <stdlib.h>
#include <stdio.h>

#define assert( cond, error ) if ( !(cond) ) { printf( "ERROR %s:%d: %s\n", __FILE__, __LINE__, error ); exit(1); }

//
// TODO:
//
// Zero optimization:
//   There can be no 1-child numbers that have two or more zeroes in them.
//     * Enumerate all numbers with one zero in them. Test if they are 1-child.
//     * Enumerate all numbers with no zeroes in them. Test.
//

/*
 *
 * d_digit = 2
 * sum: 1 min: 21
 * sum: 1 max: 89
 *
 * d_digit = 3
 * sum: 1 min: 101
 * sum: 1 max: 988
 *
 * d_digit = 4
 * sum: 1 min: 1011
 * sum: 1 max: 9998
 *
 * d_digit = 5
 * sum: 1 min: 51111
 * sum: 1 max: 59999
 *
 * d_digit = 6
 * sum: 1 min: 101111
 * sum: 1 max: 999986
 *
 * d_digit = 7
 * sum: 1 min: 1011111
 * sum: 1 max: 9999993
 *
 * d_digit = 8
 * sum: 1 min: 10111111
 * sum: 1 max: 99999998
 *
 * d_digit = 9
 * sum: 1 min: 101111111
 * sum: 1 max: 988888888
 *
 * d_digit = 10
 * There are no 1-child numbers with 10 digits.
 *
 * d_digit = 11
 * sum: 1 min: 10134567912
 * sum: 1 max: 99898654321
 *
 * d_digit = 12
 * sum: 1 min: 101111111111
 * sum: 1 max: 999999999990
 *
 * d_digit = 13
 * sum: 1 min: 1011111212174
 * sum: 1 max: 9999998986863
 *
 * d_digit = 14
 * sum: 1 min: 10111111111111
 * sum: 1 max: 99999999999930
 *
 * d_digit = 15
 * sum: 1 min: 101111111111111
 * sum: 1 max: 999999999999980
 *
 * d_digit = 16
 * sum: 1 min: 1011111111111111
 * sum: 1 max: 9999999999999996
 *
 * d_digit = 17
 * sum: 1 min: 10111111111131466
 * sum: 1 max: 99999999999999983
 *
 * d_digit = 18
 * sum: 1 min: 101111111111111111
 * sum: 1 max: 999999999999999980
 *
 * d_digit = 19
 * sum: 1 min: 1011111111113562148
 * sum: 1 max: 9999999999999999981
 *
 */

typedef struct
{
  const char *start;
  const char *end;
  unsigned long long int expectedCount;
} f_params;

f_params FP[] =
  {
    // 0
    { NULL, NULL,  0 },

    // 1
    { NULL, NULL,  9 },

    // 2
    { NULL, NULL, 20 },

    // 3
    // Number contains one of: { 0, 3, 6, 9 }
    //   and number does not sum to 3
    // Number does NOT contain one of: { 0, 3, 6, 9 }
    //   and number DOES sum to 3
    { NULL, NULL, (3*6*6-18)+(6*4*6-18)+(6*6*4-18) + 6*3*1 },

    // 4
    { "1011", "9998", 2701 },

    // 5
    // if ( !x.containsSequence( 0 ) && x[0] == 5 && x.countSequence( 5 ) == 1 ) { sum++; }
    // I.E., All numbers that begin with a 5 and have no other 5's or 0's in them
    { NULL, NULL, 8 * 8 * 8 * 8 },

    // 6
    { "101111", "999986", 109466 },

    // 7
    { "10", "99", 161022 },

    // 8
    { "1011", "9999", 13068583 },

    // 9
    { "101", "988", 2136960 },

    // 10
    { NULL, NULL, 0 },

    // 11
    { "1013456", "9989865", 71101800 },

    // 12
    { "1011111", "9999998", 55121700430 },

    // 13
    { "10111112", "99999989", 1057516028 },

    // 14
    { "10111112", "99999989", 55121700430 },    // Unsure of the expected values from here on...

    // 15
    { "10111112", "99999989", 55121700430 },

    // 16
    { "10111112", "99999989", 55121700430 },

    // 17
    { "10111112", "99999989", 55121700430 },

    // 18
    { "10111112", "99999989", 55121700430 },

    // 19
    { "10111112", "99999989", 55121700430 },
  };

unsigned long long int Process( unsigned int d_digit )
{
  unsigned char workspace[d_digit];
  unsigned int counts[d_digit];
  unsigned int count = 0;
  unsigned long long int value = 0;
  int i = 0;
  unsigned int depth = 0;
  unsigned int wEnd = d_digit - 1;
  unsigned long long int sum = 0;

  workspace[0] = 1;
  depth = 0;
  counts[0] = -1;

  do
    {
      count = depth == 0 ? 0 : counts[depth - 1];

      // Test a single candidate for 1-childness
      while ( 1 )
        {
          // Run tests on this [partial] candidate.
          unsigned long long int power = 1;
          value = 0;
          for ( i = depth; i >= 0; --i, power*=10 )
            {
              value += workspace[i] * power;
              if ( value % d_digit == 0 )
                {
                  count++;
                  if ( count > 1 ) { break; }
                }
            }
          // Process test results
          counts[depth] = count;
          if ( depth == wEnd || count > 1 )
            {
              break;
            }
          ++depth;
          workspace[depth] = 0;
          counts[depth] = -1;
        }

      // We just finished testing a single candidate.
      // Tabulate the results.
      if ( count == 1 )
        {
          ++sum;
        }

      // Increment candidate.
      int carry = 1;
      for ( i = depth; carry > 0 && i >= 0; --i )
        {
          ++workspace[i];   // Carry is always == 1 and ++ is faster.
          carry = 0;
          if ( workspace[i] > 9 )
            {
              workspace[i] = 0;
              counts[i] = -1;
              carry = 1;
            }
        }
      depth = i + 1;
      // printf( "Workspace: " ); for ( i = 0; i <= depth; ++i ) { printf( "%d", (int) workspace[i] ); } printf( "\n" );
    } while ( workspace[0] != 0 );   // Keep looping until workspace rolls over

  return sum;
}

char x[30];
unsigned int xLength = 0;
unsigned int d_digit = 0;
unsigned long long int count = 0;

unsigned long long int AddOneDigit( void )
{
  // Should we really be in here? Check the
  // termination conditions to make sure.
  if ( xLength == d_digit )
    {
      return count == 1 ? 1 : 0;
    }

  // Make room for an extra digit on the end
  xLength++;

  unsigned long long int initialCount = count;
  unsigned int i = 0;
  int start = 0;
  unsigned long long int sum = 0;

  // Try each [0-9] ending digit unless we have
  // already found a child, in which case we can
  // skip zero because it would add another child
  for ( i = (count>0); i <= 9; ++i )
  {
    count = initialCount;
    x[xLength - 1] = i;

    unsigned long int value = 0;
    unsigned long int power = 1;
    for ( start = xLength-1; start >= 0; --start, power*=10 )
    {
      value += x[start] * power;
      if ( value % d_digit == 0 )
      {
        count++;
        if ( count > 1 ) { break; }
      }
    }
    if ( count <= 1 )
      {
        sum += AddOneDigit();
      }
  }

  // Remove that extra digit we put on the end
  xLength--;

  return sum;
}

int main( int argc, char **argv )
{
  unsigned long long int d_count = 0;
  unsigned long long int sum = 0;
  unsigned int d_min = 1;
  unsigned int d_max = 19;
  int useRecursion = 0;

  if ( argc > 1 )
    {
      d_min = atoi( argv[1] );
    }
  if ( argc > 2 )
    {
      d_max = atoi( argv[2] );
    }
  if ( argc > 3 )
    {
      useRecursion = atoi( argv[3] );
    }

  printf( "useRecursion = %d, min = %d, max = %d\n\n", useRecursion, d_min, d_max );

  for ( d_digit = d_min; d_digit <= d_max; d_digit++ )
    {
      if ( FP[d_digit].start == NULL )
	{
	  d_count = FP[d_digit].expectedCount;
	}
      else
	{
          if ( useRecursion )
            {
              d_count = 0;
              unsigned int i = 0;
              for ( i = 1; i <= 9; ++i )
                {
                  x[0] = i;
                  xLength = 1;
                  count = i % d_digit == 0;
                  d_count += AddOneDigit();
                }
            }
          else
            {
              d_count = Process( d_digit );
            }
	}
      sum += d_count;
      printf( "F(%d) = %lld\t\t%lld\n", d_digit, d_count, sum );
      assert( d_count == FP[d_digit].expectedCount, "FAIL" );
    }

  return 0;
}
