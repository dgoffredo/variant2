![](choice.jpg)

variant2
========
It's not the second variant, it's a variant of two.

Why
---
Sometimes you don't have C++17. Sometimes you don't have Boost. Sometimes you
have to hustle.

What
----
`variant2_t` is a discriminated union of two distinct types. It has a minimal
interface. I just need it as a data member in a tree class.

How
---
See [test.C](test.C).

More
----
Requires C++11. Tested with Clang 6.
