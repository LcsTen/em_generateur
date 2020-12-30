# Star system

## Number of stars

As about 50% of the star systems are solitary and about 25% are binaries, we
could generalize this into probabilities. We can say that the probability that
a star system has N stars is 1/(2^N).
If the star isn't solitary, the distance between each stars is calculated.

## Type of stars

For now, all stars will be main-sequence stars, neither giants, dwarves, black
hole, nor neutron stars and the like.
The "type" of the stars is their classification using the Harvard spectral
classification. The probability is the same as the fraction of all main-sequence
stars, that is:
O - 0.00003%
B - 0.13%
A - 0.6%
F - 3%
G - 7.6%
K - 12.1%
M - 76.45%
The class subdivision are equiprobable (knowing the star is G, it has the same
probability to be G0 than to be G9, 1/10).

## Planets

Ten planets are generated. If the star isn't solitary, each planet has 50%
chance to be circumbinary, else it may orbits one of the star with the same
probability. Each planet has 50% chance to be a gas planet. The distance with
the star and the "atmosphere density" are calculated. The atmosphere density is
an arbitrary value which ranges from 0 to 120 and is used to compute the
greenhouse effects.

## Satellites

Each telluric planet has from 0 to 3 satellites, and each gas planet has from 1
to 90 satellites. The atmosphere density is calculated for each satellites.

## Habitability check

It is assumed that an astral object is habitable if it can have water on its
surface. The temperature on the surface must be comprised between -100°C and
100 °C. Each astral object must pass two checks, the "coldest" case and the
"hottest" case. The first habitable planet is chosen to be the Earth.
