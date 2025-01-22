from dataclasses import dataclass


@dataclass
class Transition:
    from_: str
    to: str
    on: str
