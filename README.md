# cowboy-shootout

A simulation for the following problem:

> In a certain town in the wild west, there is a large population of cowboys.
> According to an official decree, every town in the wild west must contain
> either 0 or 1 cowboys. The cowboys in this town have decided that they will
> have a mass shootout to reduce their population down to the requisite amount
> of cowboys. They proceed as follows:
>
> They all stand in a circle and each cowboy decides on another cowboy to shoot
> and kill (a cowboy cannot shoot himself of course). Once each cowboy has
> decided on a cowboy to shoot, they all simultaneously fire their weapon at the
> intended recipient. If more than one cowboy is left standing, they continue
> playing the game.

## Build

Running `make` will create an executable in `bin/` called `cowboy-shootout`.

## Usage

```bash
./cowboy-shootout <n_cowboys> <n_trials>
```

## Example

```bash
$ ./cowboy-shootout 3 1000

For 3 cowboys, we have a 0.75 probability of one cowboy surviving [n_trials: 1000]
```
