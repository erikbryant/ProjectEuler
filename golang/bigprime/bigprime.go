package bigprime

import (
	"fmt"
	"math/big"
)

var Primes [1000000]*big.Int

// http://primes.utm.edu/prove/prove2_3.html
func nextLowerPrime(n *big.Int) *big.Int {
	return n
}

func Init(max, min *big.Int) {
	fmt.Println(max)
	fmt.Println(nextLowerPrime(min))
	Primes[0] = max
	Primes[1] = min
	fmt.Println(Primes[0])
	fmt.Println(Primes[1])
}
