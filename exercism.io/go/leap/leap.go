package leap

func IsLeapYear(year int) bool {
	if (year > 0) && (year%4 == 0) && !((year%100 == 0) && (year%400 != 0)) {
		return true
	}

	return false
}
