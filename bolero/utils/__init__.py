from module_loader import from_yaml, from_dict
from validation import check_random_state


__all__ = ["from_yaml", "from_dict", "check_random_state"]


class NonContextualException(Exception):
    """ Exception thrown in methods not supported in contextual scenarios."""
    pass


class ContextualException(Exception):
    """ Exception thrown in methods not supported in non-contextual scenarios."""
    pass
