# Phases

The world generation will have a few phases.

## Star system generation

The stars are generated first, then a few planets are generated, and may be
either circumbinary or not. Finally, the satellites are generated. It is assumed
that all orbits are circle and stable.
The first habitable planet is chosen. If no habitable planet exists, the system
is rejected.
(See STAR_SYSTEM.md)

## Topographic generation

The surface details of the Earth are generated. For now, this phase is really
simple.

## Evolution race

The first living being appears on Earth. It will proliferate, move and mutate,
creating new species on the process. This phase continues until a species
intelligent enough to create a civilisation is created.

## Creation of sedentary settlements

All species intelligent enough to create a civilisation will roam the Earth as
nomadic groups. They will create a settlement on the first fertile land they
find (or try to mix in, if another species already created a settlement there).

## Creation of civilisation

Each settlement becomes the capital of a country with a simple political system
(a "chief" and the "others"). Those countries will try to expand, be at war with
each other and eventually be divided into new countries, while their political
systems change and become more complex. This phase continues until stabilization
(or after a specified amount of time, or after a manual interruption).

## Beginning of the interactive era

The world is sucessfully generated. The user may browse the result and/or skip
more time to see the civilisations evolve.
