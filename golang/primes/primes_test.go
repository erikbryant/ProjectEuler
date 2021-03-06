package primes

import (
	"testing"
)

func init() {
	Init(false)
}

func TestS(t *testing.T) {
	primeVals := []struct {
		n        int
		expected bool
	}{
		{1, true},
		{2, true},
		{3, true},
		{4, false},
		{5, true},
		{6, false},
		{7, true},
		{101, true},
	}

	for _, primeVal := range primeVals {
		isPrime := Prime(primeVal.n)
		if isPrime != primeVal.expected {
			t.Errorf("ERROR: For %d expected %t, got %t", primeVal.n, primeVal.expected, isPrime)
		}
	}
}
