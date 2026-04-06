import sys
from pathlib import Path

# ------------------------------------------------------------------------------
def get_row_idxs_match(data: list[str], pattern: str) -> list[int]:
    rows = (row.lstrip() for row in data)
    return [i for i, row in enumerate(rows) if row.startswith(pattern)]


# //////////////////////////////////////////////////////////////////////////////
class Injection:
    def __init__(self, path_inject: Path):
        data = path_inject.read_text().splitlines()
        idxs_inject_h = get_row_idxs_match(data, "#GARLIC_INJECT_H")
        idxs_inject_c = get_row_idxs_match(data, "#GARLIC_INJECT_C")

        assert len(idxs_inject_h) == 1, f"Expected exactly one #GARLIC_INJECT_H in '{path_inject.name}'"
        assert len(idxs_inject_c) == 1, f"Expected exactly one #GARLIC_INJECT_C in '{path_inject.name}'"

        idx_h = idxs_inject_h[0]
        idx_c = idxs_inject_c[0]
        assert idx_h < idx_c, f"Expected #GARLIC_INJECT_H to come before #GARLIC_INJECT_C ('{path_inject.name}')"

        self.h: list[str] = data[idx_h + 1:idx_c]
        self.c: list[str] = data[idx_c + 1:]

    # --------------------------------------------------------------------------
    def get_injection_h(self) -> list[str]:
        return self.h

    # --------------------------------------------------------------------------
    def get_injection_c(self) -> list[str]:
        return self.c


# //////////////////////////////////////////////////////////////////////////////
class Target:
    def __init__(self, path_target: Path):
        self.data      : list[str] = path_target.read_text().splitlines()
        self.idxs_start: list[int] = get_row_idxs_match(self.data, "// GARLIC_INJECT_START")
        self.idxs_end  : list[int] = get_row_idxs_match(self.data, "// GARLIC_INJECT_END")
        self.path : Path = path_target

        assert len(self.idxs_start) == len(self.idxs_end),\
            f"Expected the same number of GARLIC_INJECT_START and GARLIC_INJECT_END ('{self.path.name}')"
        assert all(s < e for s, e in zip(self.idxs_start, self.idxs_end)),\
            f"Expected GARLIC_INJECT_START to come before GARLIC_INJECT_END ('{self.path.name}')"

        self.tags = [self._get_tag(idx) for idx in self.idxs_start]


    # --------------------------------------------------------------------------
    def apply_injections(self, injects: dict[str, Injection]):
        out = []
        prev_end = 0
        for start,end,tag in zip(self.idxs_start, self.idxs_end, self.tags):
            if tag not in injects:
                raise KeyError(f"Tag '{tag}' not found in injects")

            out.extend(self.data[prev_end:start + 1])
            out.extend(self._get_injection(injects[tag]))
            prev_end = end

        self.data = out + self.data[prev_end:]


    # --------------------------------------------------------------------------
    def save(self, pad_newline = True) -> None:
        out = '\n'.join(self.data)
        if pad_newline and not out.endswith('\n'):
            out += '\n'
        self.path.write_text(out)

    # --------------------------------------------------------------------------
    def _get_tag(self, idx_row: int) -> str:
        row = self.data[idx_row].lstrip()
        _,tag = row.split(':')
        return tag


    # --------------------------------------------------------------------------
    @classmethod
    def _get_injection(cls, inject: Injection) -> list[str]:
        raise NotImplementedError("Subclasses must implement _get_injection")


# //////////////////////////////////////////////////////////////////////////////
class TargetHeader(Target):
    @classmethod
    def _get_injection(cls, inject: Injection) -> list[str]:
        return inject.get_injection_h()


# //////////////////////////////////////////////////////////////////////////////
class TargetSource(Target):
    @classmethod
    def _get_injection(cls, inject: Injection) -> list[str]:
        return inject.get_injection_c()


# //////////////////////////////////////////////////////////////////////////////

# ------------------------------------------------------------------------------
def main():
    paths_inject = FOLDER_INJECTS.glob("*.inject")
    injects = {path.stem: Injection(path) for path in paths_inject}
    gen_targets_h = [TargetHeader(path) for path in FOLDER_HEADERS.rglob("*.h")]
    gen_targets_c = [TargetSource(path) for path in FOLDER_SOURCES.rglob("*.c")]

    targets = [t for t in gen_targets_h if t.tags] + [t for t in gen_targets_c if t.tags]
    for target in targets:
        target.apply_injections(injects)
        target.save()


################################################################################
if __name__ == "__main__":
    FOLDER_SOURCES = Path(sys.argv[1])
    FOLDER_HEADERS = Path(sys.argv[2])
    FOLDER_INJECTS = Path(sys.argv[3])
    main()


################################################################################
# python3 injector.py ../src ../include inject
