> ./crear_puntos.cpp
>
> 62 | `distancias.reserve((N * (N - 1)) / 2);`
>
> Not freed (?)

> ./crear_puntos.cpp
>
> 63,64 | use of `double`
>
> Is it optimal?

> ./crear_puntos.cpp
>
> Where is `Punto` defined?
>
> Found // crear_puntos.h

> ./crear_puntos.cpp
>
> Clean-up defined for `CrearPuntos::CrearPuntosNHeap` but not for `CrearPuntos::CrearPuntosNArreglo`
>
> An inner method could be defined for cleanup if it is an oversight

> ./crear_puntos.cpp
>
> 91 | `CrearPuntos::CrearPuntosNHeap` implements basic depuration
>
> Could be made more strict, as for leq0

> ./crear_puntos.cpp
>
> 114 | Is that the correct implementation?
>
> Found // Yes