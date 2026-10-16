"""
File 1 - Classical General Trees (children[])
==============================================

Representation used throughout the file
---------------------------------------
Node:
    key          # the value stored in the node
    children[]   # list of child nodes
    nb_children  # number of children (== len(children))

Conventions
-----------
* An empty tree is None (the NULL of the exercise statements).
* Level / depth of the root is 0.
* height(None) = -1, height(leaf) = 0.
* "Internal node" = a node with at least one child.
* Functions return the value stated in their docstring; when a result does
  not exist (no internal node, key not found...), the docstring says what is
  returned (None, -1, [] ...).

Sections
--------
 1. Basic functions
 2. Height, depth, and arity
 3. Traversals
 4. Aggregations and statistics
 5. Searching and locating nodes
 6. Structural properties
 7. Relationships between subtrees
 8. Transformations
 9. Representation and notation
"""

from collections import deque


# ---------------------------------------------------------------------------
# Node definition and helpers
# ---------------------------------------------------------------------------

class Node:
    def __init__(self, key, children=None):
        self.key = key
        self.children = list(children) if children else []
        self.nb_children = len(self.children)

    def __repr__(self):
        return to_linear(self)


def node(key, *children):
    """Shortcut to build a tree: node(1, node(2), node(3, node(4)))."""
    return Node(key, list(children))


def _levels(T):
    """Return a list of lists of nodes, one list per level (helper)."""
    result = []
    if T is None:
        return result
    current = [T]
    while current:
        result.append(current)
        current = [c for n in current for c in n.children]
    return result


# ===========================================================================
# 1. BASIC FUNCTIONS
# ===========================================================================

def is_empty(T):
    """Return True if T is the empty tree (None)."""
    return T is None


def get_root(T):
    """Return the root node of T (None if T is empty)."""
    return T


def count_children(T):
    """Return the number of direct children of the root (0 if T is empty)."""
    return 0 if T is None else T.nb_children


def is_leaf(T):
    """Return True if the root of T exists and has no child."""
    return T is not None and T.nb_children == 0


def is_internal(T):
    """Return True if the root of T exists and has at least one child."""
    return T is not None and T.nb_children > 0


def size(T):
    """Return the total number of nodes in T (0 if empty)."""
    if T is None:
        return 0
    return 1 + sum(size(c) for c in T.children)


def count_leaves(T):
    """Return the number of leaves in T (0 if empty)."""
    if T is None:
        return 0
    if T.nb_children == 0:
        return 1
    return sum(count_leaves(c) for c in T.children)


def count_internal(T):
    """Return the number of internal nodes in T (0 if empty)."""
    if T is None or T.nb_children == 0:
        return 0
    return 1 + sum(count_internal(c) for c in T.children)


def count_nodes_at_level(T, k):
    """Return the number of nodes at level k (root = level 0)."""
    if T is None or k < 0:
        return 0
    if k == 0:
        return 1
    return sum(count_nodes_at_level(c, k - 1) for c in T.children)


def count_nodes_with_key(T, x):
    """Return the number of nodes whose key equals x."""
    if T is None:
        return 0
    return (T.key == x) + sum(count_nodes_with_key(c, x) for c in T.children)


# ===========================================================================
# 2. HEIGHT, DEPTH, AND ARITY
# ===========================================================================

def height(T):
    """Return the height of T: -1 if empty, 0 for a single node."""
    if T is None:
        return -1
    return 1 + max((height(c) for c in T.children), default=-1)


def depth(T, x):
    """Return the depth of the first node (prefix order) with key x, -1 if absent."""
    if T is None:
        return -1
    if T.key == x:
        return 0
    for c in T.children:
        d = depth(c, x)
        if d != -1:
            return d + 1
    return -1


def max_depth(T):
    """Return the maximum depth of any node (-1 if T is empty)."""
    return height(T)


def arity(T):
    """Return the number of children of the root (0 if empty)."""
    return count_children(T)


def max_arity(T):
    """Return the maximum number of children of any node (0 if empty)."""
    if T is None:
        return 0
    return max([T.nb_children] + [max_arity(c) for c in T.children])


def min_arity(T):
    """Return the minimum number of children among internal nodes (None if there is none)."""
    if T is None or T.nb_children == 0:
        return None
    best = T.nb_children
    for c in T.children:
        m = min_arity(c)
        if m is not None and m < best:
            best = m
    return best


def _arity_sum_count(T):
    """Return (sum of arities of internal nodes, number of internal nodes)."""
    if T is None or T.nb_children == 0:
        return (0, 0)
    s, n = T.nb_children, 1
    for c in T.children:
        cs, cn = _arity_sum_count(c)
        s, n = s + cs, n + cn
    return (s, n)


def average_arity(T):
    """Return the average number of children over internal nodes (None if none)."""
    s, n = _arity_sum_count(T)
    return None if n == 0 else s / n


def count_nodes_at_depth(T, k):
    """Return the number of nodes at depth k."""
    if T is None or k < 0:
        return 0
    if k == 0:
        return 1
    return sum(count_nodes_at_depth(c, k - 1) for c in T.children)


def widest_level(T):
    """Return the index of the level with the most nodes (smallest index on ties, -1 if empty)."""
    counts = [len(l) for l in _levels(T)]
    if not counts:
        return -1
    return counts.index(max(counts))


def width(T):
    """Return the maximum number of nodes at any single level (0 if empty)."""
    return max((len(l) for l in _levels(T)), default=0)


# ===========================================================================
# 3. TRAVERSALS
# ===========================================================================

def prefix(T):
    """Return the list of keys: root first, then each child subtree left to right."""
    if T is None:
        return []
    out = [T.key]
    for c in T.children:
        out += prefix(c)
    return out


def suffix(T):
    """Return the list of keys: each child subtree left to right, then the root."""
    if T is None:
        return []
    out = []
    for c in T.children:
        out += suffix(c)
    return out + [T.key]


def level_order(T):
    """Return the list of keys level by level, left to right."""
    return [n.key for l in _levels(T) for n in l]


def print_level(T, k):
    """Print (one per line) the keys of all nodes at level k, left to right."""
    if T is None or k < 0:
        return
    if k == 0:
        print(T.key)
        return
    for c in T.children:
        print_level(c, k - 1)


def reverse_prefix(T):
    """Return the list of keys: root, then its children visited right to left."""
    if T is None:
        return []
    out = [T.key]
    for c in reversed(T.children):
        out += reverse_prefix(c)
    return out


def leftmost_leaf(T):
    """Return the first leaf met in prefix order (None if T is empty)."""
    if T is None:
        return None
    if T.nb_children == 0:
        return T
    return leftmost_leaf(T.children[0])


def rightmost_leaf(T):
    """Return the last leaf met in prefix order (None if T is empty)."""
    if T is None:
        return None
    if T.nb_children == 0:
        return T
    return rightmost_leaf(T.children[-1])


# ===========================================================================
# 4. AGGREGATIONS AND STATISTICS   (keys are assumed to be numbers)
# ===========================================================================

def sum_keys(T):
    """Return the sum of all keys (0 if empty)."""
    if T is None:
        return 0
    return T.key + sum(sum_keys(c) for c in T.children)


def min_key(T):
    """Return the minimum key (None if empty)."""
    if T is None:
        return None
    best = T.key
    for c in T.children:
        m = min_key(c)
        if m is not None and m < best:
            best = m
    return best


def max_key(T):
    """Return the maximum key (None if empty)."""
    if T is None:
        return None
    best = T.key
    for c in T.children:
        m = max_key(c)
        if m is not None and m > best:
            best = m
    return best


def _sum_count(T):
    """Return the pair (sum of keys, number of nodes)."""
    if T is None:
        return (0, 0)
    s, n = T.key, 1
    for c in T.children:
        cs, cn = _sum_count(c)
        s, n = s + cs, n + cn
    return (s, n)


def average_key(T):
    """Return the average of all keys (None if empty)."""
    s, n = _sum_count(T)
    return None if n == 0 else s / n


def sum_leaves(T):
    """Return the sum of the keys of the leaves (0 if empty)."""
    if T is None:
        return 0
    if T.nb_children == 0:
        return T.key
    return sum(sum_leaves(c) for c in T.children)


def count_even(T):
    """Return the number of nodes with an even key."""
    if T is None:
        return 0
    return (T.key % 2 == 0) + sum(count_even(c) for c in T.children)


def count_greater(T, x):
    """Return the number of nodes whose key is strictly greater than x."""
    if T is None:
        return 0
    return (T.key > x) + sum(count_greater(c, x) for c in T.children)


def max_subtree_size(T):
    """Return the size of the largest child subtree of the root (0 if no child)."""
    if T is None:
        return 0
    return max((size(c) for c in T.children), default=0)


def sum_level(T, k):
    """Return the sum of the keys at level k."""
    if T is None or k < 0:
        return 0
    if k == 0:
        return T.key
    return sum(sum_level(c, k - 1) for c in T.children)


def average_subtree_size(T):
    """Return the average size of the root's child subtrees (None if no child)."""
    if T is None or T.nb_children == 0:
        return None
    return sum(size(c) for c in T.children) / T.nb_children


# ===========================================================================
# 5. SEARCHING AND LOCATING NODES
# ===========================================================================

def contains(T, x):
    """Return True if some node has key x."""
    if T is None:
        return False
    return T.key == x or any(contains(c, x) for c in T.children)


def find_node(T, x):
    """Return the first node (prefix order) with key x, None if absent."""
    if T is None:
        return None
    if T.key == x:
        return T
    for c in T.children:
        r = find_node(c, x)
        if r is not None:
            return r
    return None


def count_occurrences(T, x):
    """Return the number of nodes with key x."""
    return count_nodes_with_key(T, x)


def find_min_node(T):
    """Return a node holding the minimum key (first in prefix order), None if empty."""
    if T is None:
        return None
    best = T
    for c in T.children:
        r = find_min_node(c)
        if r is not None and r.key < best.key:
            best = r
    return best


def find_max_node(T):
    """Return a node holding the maximum key (first in prefix order), None if empty."""
    if T is None:
        return None
    best = T
    for c in T.children:
        r = find_max_node(c)
        if r is not None and r.key > best.key:
            best = r
    return best


def first_matching(T, p):
    """Return the first node (prefix order) whose key satisfies predicate p, None if none."""
    if T is None:
        return None
    if p(T.key):
        return T
    for c in T.children:
        r = first_matching(c, p)
        if r is not None:
            return r
    return None


def path_to(T, x):
    """Return the list of keys from the root to the first node with key x (None if absent)."""
    if T is None:
        return None
    if T.key == x:
        return [T.key]
    for c in T.children:
        p = path_to(c, x)
        if p is not None:
            return [T.key] + p
    return None


def parent_of(T, x):
    """Return the parent node of the first node with key x (None if x is the root or absent)."""
    if T is None:
        return None
    for c in T.children:
        if c.key == x:
            return T
    for c in T.children:
        r = parent_of(c, x)
        if r is not None:
            return r
    return None


def are_siblings(T, x, y):
    """Return True if two distinct nodes with keys x and y share the same parent."""
    if T is None:
        return False
    for i in range(T.nb_children):
        for j in range(T.nb_children):
            if i != j and T.children[i].key == x and T.children[j].key == y:
                return True
    return any(are_siblings(c, x, y) for c in T.children)


def nodes_after(T, x, order="prefix"):
    """Return the list of keys that come after the first occurrence of x in the
    given traversal order ("prefix", "suffix" or "level"). [] if x is absent."""
    orders = {"prefix": prefix, "suffix": suffix, "level": level_order}
    seq = orders[order](T)
    if x not in seq:
        return []
    return seq[seq.index(x) + 1:]


# ===========================================================================
# 6. STRUCTURAL PROPERTIES   (all return a Boolean; empty tree -> True)
# ===========================================================================

def all_positive(T):
    """Return True if every key is strictly positive."""
    if T is None:
        return True
    return T.key > 0 and all(all_positive(c) for c in T.children)


def all_leaves_even(T):
    """Return True if every leaf has an even key."""
    if T is None:
        return True
    if T.nb_children == 0:
        return T.key % 2 == 0
    return all(all_leaves_even(c) for c in T.children)


def all_internal_have_children(T, cond):
    """Return True if cond(nb_children) holds for every internal node.
    Example: cond = lambda n: n >= 2."""
    if T is None or T.nb_children == 0:
        return True
    return cond(T.nb_children) and all(all_internal_have_children(c, cond) for c in T.children)


def all_arity_at_most(T, k):
    """Return True if every node has at most k children."""
    if T is None:
        return True
    return T.nb_children <= k and all(all_arity_at_most(c, k) for c in T.children)


def all_arity_equal(T, k):
    """Return True if every internal node has EXACTLY k children."""
    return all_internal_have_children(T, lambda n: n == k)


def is_n_ary(T, k):
    """Return True if every node has AT MOST k children (k is a maximum)."""
    return all_arity_at_most(T, k)


def is_chain(T):
    """Return True if every node has at most one child."""
    return all_arity_at_most(T, 1)


def is_star(T):
    """Return True if all children of the root are leaves."""
    if T is None:
        return True
    return all(c.nb_children == 0 for c in T.children)


def _leaf_depths(T, d=0):
    if T is None:
        return []
    if T.nb_children == 0:
        return [d]
    return [x for c in T.children for x in _leaf_depths(c, d + 1)]


def all_leaves_same_depth(T):
    """Return True if all leaves are at the same depth."""
    return len(set(_leaf_depths(T))) <= 1


def _arities(T):
    if T is None or T.nb_children == 0:
        return []
    return [T.nb_children] + [a for c in T.children for a in _arities(c)]


def is_perfect(T):
    """Return True if all internal nodes have the same number of children
    and all leaves have the same depth."""
    return len(set(_arities(T))) <= 1 and all_leaves_same_depth(T)


def has_unary_node(T):
    """Return True if some node has exactly one child."""
    if T is None:
        return False
    return T.nb_children == 1 or any(has_unary_node(c) for c in T.children)


def every_child_larger(T):
    """Return True if every child key is strictly greater than its parent's key."""
    if T is None:
        return True
    return all(c.key > T.key and every_child_larger(c) for c in T.children)


def _morechildren(T, parent_arity):
    if T is None or T.nb_children == 0:
        return True
    if parent_arity is not None and T.nb_children <= parent_arity:
        return False
    return all(_morechildren(c, T.nb_children) for c in T.children)


def morechildren(T):
    """Return True if every non-root internal node has strictly more children
    than its parent."""
    return _morechildren(T, None)


# ===========================================================================
# 7. RELATIONSHIPS BETWEEN SUBTREES
# ===========================================================================

def same_tree(T, U):
    """Return True if T and U have identical structure AND keys (same child order)."""
    if T is None or U is None:
        return T is None and U is None
    if T.key != U.key or T.nb_children != U.nb_children:
        return False
    return all(same_tree(a, b) for a, b in zip(T.children, U.children))


def same_structure(T, U):
    """Return True if T and U have the same shape, ignoring keys."""
    if T is None or U is None:
        return T is None and U is None
    if T.nb_children != U.nb_children:
        return False
    return all(same_structure(a, b) for a, b in zip(T.children, U.children))


def symmetric(T, U):
    """Return True if U is the mirror image of T (same keys, children reversed everywhere)."""
    if T is None or U is None:
        return T is None and U is None
    if T.key != U.key or T.nb_children != U.nb_children:
        return False
    return all(symmetric(a, b) for a, b in zip(T.children, reversed(U.children)))


def is_symmetric(T):
    """Return True if T is its own mirror image."""
    return symmetric(T, T)


def is_subtree(T, U):
    """Return True if U (with keys) occurs as a complete subtree of T.
    The empty tree U is a subtree of every tree."""
    if U is None:
        return True
    if T is None:
        return False
    return same_tree(T, U) or any(is_subtree(c, U) for c in T.children)


def count_equal_subtrees(T):
    """Return the number of unordered pairs of the root's children whose
    subtrees have the same structure."""
    if T is None:
        return 0
    n = T.nb_children
    return sum(1 for i in range(n) for j in range(i + 1, n)
               if same_structure(T.children[i], T.children[j]))


def largest_subtree(T):
    """Return the child of the root with the greatest size (first on ties), None if no child."""
    if T is None or T.nb_children == 0:
        return None
    best = T.children[0]
    for c in T.children[1:]:
        if size(c) > size(best):
            best = c
    return best


def all_subtrees_satisfy(T, p):
    """Return True if predicate p (taking a tree) holds for EVERY subtree of T,
    including T itself."""
    if T is None:
        return True
    return p(T) and all(all_subtrees_satisfy(c, p) for c in T.children)


def are_all_children_equal(T):
    """Return True if all direct child subtrees of the root are identical (keys included)."""
    if T is None or T.nb_children <= 1:
        return True
    return all(same_tree(T.children[0], c) for c in T.children[1:])


# ===========================================================================
# 8. TRANSFORMATIONS   (return a NEW tree unless stated otherwise)
# ===========================================================================

def copy_tree(T):
    """Return a deep copy of T."""
    if T is None:
        return None
    return Node(T.key, [copy_tree(c) for c in T.children])


def mirror(T):
    """Return a copy of T where the children order is reversed at every node."""
    if T is None:
        return None
    return Node(T.key, [mirror(c) for c in reversed(T.children)])


def map_tree(T, f):
    """Return a copy of T where every key k is replaced by f(k)."""
    if T is None:
        return None
    return Node(f(T.key), [map_tree(c, f) for c in T.children])


def increment_keys(T):
    """Return a copy of T where every key is increased by one."""
    return map_tree(T, lambda k: k + 1)


def replace_key(T, x, y):
    """Return a copy of T where every key equal to x becomes y."""
    return map_tree(T, lambda k: y if k == x else k)


def remove_leaves(T):
    """Return a copy of T without its leaves. If T is a single leaf, the result is None."""
    if T is None or T.nb_children == 0:
        return None
    kept = [remove_leaves(c) for c in T.children]
    return Node(T.key, [c for c in kept if c is not None])


def prune(T, k):
    """Return a copy of T where all nodes at depth k (and their subtrees) are removed.
    prune(T, 0) is None."""
    if T is None or k <= 0:
        return None
    return Node(T.key, [c for c in (prune(c, k - 1) for c in T.children) if c is not None])


def filter_tree(T, p):
    """Return a copy keeping a node only if its key satisfies p AND its parent was kept.
    A node failing p is removed together with its whole subtree.
    Returns None if the root fails p."""
    if T is None or not p(T.key):
        return None
    return Node(T.key, [c for c in (filter_tree(c, p) for c in T.children) if c is not None])


# ===========================================================================
# 9. REPRESENTATION AND NOTATION
# ===========================================================================

def to_linear(T):
    """Return the parenthesized notation, e.g. 1(2,3(4)). Empty tree -> ''."""
    if T is None:
        return ""
    if T.nb_children == 0:
        return str(T.key)
    return str(T.key) + "(" + ",".join(to_linear(c) for c in T.children) + ")"


def from_linear(s):
    """Build a tree from parenthesized notation like '1(2,3(4))'.
    Keys are read as int when possible, otherwise kept as strings.
    '' -> None."""
    s = s.replace(" ", "")
    if s == "":
        return None

    def parse(i):
        j = i
        while j < len(s) and s[j] not in "(),":
            j += 1
        tok = s[i:j]
        try:
            key = int(tok)
        except ValueError:
            key = tok
        children = []
        if j < len(s) and s[j] == "(":
            j += 1
            while True:
                child, j = parse(j)
                children.append(child)
                if s[j] == ",":
                    j += 1
                else:
                    break
            j += 1  # skip ')'
        return Node(key, children), j

    tree, _ = parse(0)
    return tree


def serialize(T):
    """Return a flat list [key, nb_children, key, nb_children, ...] in prefix order.
    Empty tree -> []."""
    if T is None:
        return []
    out = [T.key, T.nb_children]
    for c in T.children:
        out += serialize(c)
    return out


def deserialize(seq):
    """Rebuild the tree from the list produced by serialize ([] -> None)."""
    if not seq:
        return None
    it = iter(seq)

    def build():
        key = next(it)
        n = next(it)
        return Node(key, [build() for _ in range(n)])

    return build()


def count_subtrees(T):
    """Return the number of rooted subtrees of T (every node roots one), T included."""
    return size(T)


def is_valid_tree(T):
    """Return True if T is a valid tree: every nb_children matches len(children),
    every child is a Node, and no node appears twice (no cycle / sharing)."""
    seen = set()

    def check(n):
        if not isinstance(n, Node) or id(n) in seen:
            return False
        seen.add(id(n))
        if n.nb_children != len(n.children):
            return False
        return all(check(c) for c in n.children)

    return True if T is None else check(T)


# ---------------------------------------------------------------------------
# Quick self-test:  python general_trees_exercises.py
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    #           1
    #         / | \
    #        2  3  4
    #       / \     |
    #      5   6    7
    T = from_linear("1(2(5,6),3,4(7))")

    assert size(T) == 7 and count_leaves(T) == 4 and count_internal(T) == 3
    assert height(T) == 2 and max_arity(T) == 3 and min_arity(T) == 1
    assert count_nodes_at_level(T, 2) == 3 and width(T) == 3 and widest_level(T) == 1
    assert prefix(T) == [1, 2, 5, 6, 3, 4, 7]
    assert suffix(T) == [5, 6, 2, 3, 7, 4, 1]
    assert level_order(T) == [1, 2, 3, 4, 5, 6, 7]
    assert reverse_prefix(T) == [1, 4, 7, 3, 2, 6, 5]
    assert sum_keys(T) == 28 and max_key(T) == 7 and min_key(T) == 1
    assert path_to(T, 6) == [1, 2, 6] and depth(T, 7) == 2
    assert parent_of(T, 5).key == 2 and are_siblings(T, 5, 6)
    assert nodes_after(T, 3) == [4, 7]
    assert not is_chain(T) and is_n_ary(T, 3) and not is_perfect(T)
    assert same_tree(T, copy_tree(T)) and same_structure(T, increment_keys(T))
    assert symmetric(T, mirror(T)) and not is_symmetric(T)
    assert is_subtree(T, from_linear("4(7)"))
    assert to_linear(remove_leaves(T)) == "1(2,4)"
    assert to_linear(prune(T, 2)) == "1(2,3,4)"
    assert to_linear(filter_tree(T, lambda k: k != 2)) == "1(3,4(7))"
    assert deserialize(serialize(T)) is not None and same_tree(T, deserialize(serialize(T)))
    assert from_linear(to_linear(T)).key == 1 and to_linear(T) == "1(2(5,6),3,4(7))"
    assert is_valid_tree(T) and count_subtrees(T) == 7
    print("All tests passed.")
