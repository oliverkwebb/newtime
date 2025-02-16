# newtime - An example time library to show what C's one could have been\

The C time library among the most hacky and full of outdated heuristics. This library and the
article created both are meant to demonstrate the subtler flaws of the inbuilt library. And show
what could've been of the time library.

## Use

`date_t` is a floating point value of seconds since the epoch gotten by `date()`, this can be passed either
to `tocal()`/`wdayof()`/`ydayof()` to directly handle human-friendly values or passed to `printfdate()` to directly
print the time as a string based off these printf-style formatters:

* s - seconds
 - Us - microseconds
 - Ns - nanoseconds
* m - minutes
* h - hours
 - ch - clock hours (12-hour time)
 - ih - indicator for hours (AM/PM)
* d - Month day
* w - Full weekday
 - aw - Abbreviated weekday
 - nw - Number of weekday
* M - month name
 - aM - Abbreviated month
 - nM - Number of month
* y - year
 - Dy - day of year
 - Cy - Century
* z - zone name
 - oz - zone offset
 - nz - index name of zone (i.e. `America/New_York`)

The timezone API in C is particularly horrendous. In this library you can get the name of a timezone with `tznameat()`,
the offset with `tzoffat()`, the time in the timezone with `intz()`, the time in your local timezone with `inmytz()`
(and the timezone itself with `mytz()`).