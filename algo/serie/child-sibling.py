"""
File 2 - First-Child / Next-Sibling Trees
==========================================

Representation used throughout the file
---------------------------------------
Node:
    key
    first_child    # link DOWN to the first child (None if the node is a leaf)
    next_sibling   # link RIGHT to the next child of the same parent (None if last)

Conventions
-----------
* None represents an absent link, and the empty tree.
* The ROOT of a tree has no sibling: root.next_sibling is None.
  Every function of sections 1-9 receives the root of a tree (unless its
  docstring says it receives "a node of a sibling chain").
* Level / depth of the root is 0.  height(None) = -1, height(leaf) = 0.
* "Internal node" = a node with at least one child.
* There is NO parent pointer: a parent must be discovered while going down
  from the root.

The two basic moves (the whole difficulty of this file)
-------------------------------------------------------
* Going DOWN into a child's subtree  -> recursive call on first_child side.
* Going ACROSS the remaining children -> loop on next_sibling.

    c = T.first_child
    while c is not None:
        ...            # work on child c (usually a recursive call)
        c = c.next_sibling

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
 9. Conversions and linear notation
10. Extra: sibling chains and link manipulation
"""


# ---------------------------------------------------------------------------
# Node definitions and helpers
# ---------------------------------------------------------------------------

class Node:
    def __init__(self, key, first_child=None, next_sibling=None):
        self.key = key
        self.first_child = first_child
        self.next_sibling = next_sibling

    def __repr__(self):
        return to_linear(self)


class ClassicalNode:
    """Classical representation (used only by the conversion exercises)."""

    def __init__(self, key, children=None):
        self.key = key
        self.children = list(children) if children else []
        self.nb_children = len(self.children)


def _kids(T):
    """Iterate over the children of T by following first_child, then next_sibling."""
    c = T.first_child
    while c is not None:
        yield c
        c = c.next_sibling


def _build(key, kids):
    """Create a node with the given key whose children are the (fresh, unlinked)
    trees of the list kids, in that order."""
    n = Node(key)
    prev = None
    for k in kids:
        if prev is None:
            n.first_child = k
        else:
            prev.next_sibling = k
        prev = k
    return n


def node(key, *children):
    """Shortcut to build a tree: node(1, node(2), node(3, node(4)))."""
    return _build(key, list(children))


def _levels(T):
    """Return a list of lists of nodes, one list per level."""
    result = []
    cur = [T] if T is not None else []
    while cur:
        result.append(cur)
        cur = [c for n in cur for c in _kids(n)]
    return result


# ===========================================================================
# 1. BASIC FUNCTIONS
# ===========================================================================

def is_empty(T):
    """Return True if T is the empty tree (None)."""
    return T is None


def get_root(T):
    """Return the root of the tree (None if empty)."""
    return T


def is_leaf(T):
    """Return True if the node exists and has no child."""
    return T is not None and T.first_child is None


def is_internal(T):
    """Return True if the node exists and has at least one child."""
    return T is not None and T.first_child is not None


def count_children(T):
    """Return the number of direct children of the node (0 if empty)."""
    if T is None:
        return 0
    n = 0
    c = T.first_child
    while c is not None:
        n += 1
        c = c.next_sibling
    return n


def size(T):
    """Return the total number of nodes of the tree rooted at T (0 if empty)."""
    if T is None:
        return 0
    total = 1
    for c in _kids(T):
        total += size(c)
    return total


def count_leaves(T):
    """Return the number of leaves (0 if empty)."""
    if T is None:
        return 0
    if T.first_child is None:
        return 1
    return sum(count_leaves(c) for c in _kids(T))


def count_internal(T):
    """Return the number of internal nodes (0 if empty)."""
    if T is None or T.first_child is None:
        return 0
    return 1 + sum(count_internal(c) for c in _kids(T))


def count_nodes_with_key(T, x):
    """Return the number of nodes whose key equals x."""
    if T is None:
        return 0
    return (T.key == x) + sum(count_nodes_with_key(c, x) for c in _kids(T))


def count_siblings(T):
    """T is a node OF A SIBLING CHAIN (not necessarily the root of the whole tree).
    Return the number of nodes in the chain starting at T: T and all the
    nodes following it through next_sibling (0 if T is None)."""
    n = 0
    while T is not None:
        n += 1
        T = T.next_sibling
    return n


# ===========================================================================
# 2. HEIGHT, DEPTH, AND ARITY
# ===========================================================================

def height(T):
    """Return the height of the tree: -1 if empty, 0 for a single node."""
    if T is None:
        return -1
    h = -1
    for c in _kids(T):
        h = max(h, height(c))
    return 1 + h


def depth(T, x):
    """Return the depth of the first node (prefix order) with key x, -1 if absent."""
    if T is None:
        return -1
    if T.key == x:
        return 0
    for c in _kids(T):
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
    best = count_children(T)
    for c in _kids(T):
        best = max(best, max_arity(c))
    return best


def min_arity(T):
    """Return the minimum number of children among internal nodes (None if none)."""
    if T is None or T.first_child is None:
        return None
    best = count_children(T)
    for c in _kids(T):
        m = min_arity(c)
        if m is not None and m < best:
            best = m
    return best


def _arity_sum_count(T):
    """Return (sum of arities of internal nodes, number of internal nodes)."""
    if T is None or T.first_child is None:
        return (0, 0)
    s, n = count_children(T), 1
    for c in _kids(T):
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
    return sum(count_nodes_at_depth(c, k - 1) for c in _kids(T))


def width(T):
    """Return the maximum number of nodes at any single level (0 if empty)."""
    return max((len(l) for l in _levels(T)), default=0)


def widest_level(T):
    """Return the index of the level with the most nodes (smallest index on ties, -1 if empty)."""
    counts = [len(l) for l in _levels(T)]
    if not counts:
        return -1
    return counts.index(max(counts))


# ===========================================================================
# 3. TRAVERSALS
# ===========================================================================

def prefix(T):
    """Return the list of keys: root first, then each child subtree left to right."""
    if T is None:
        return []
    out = [T.key]
    for c in _kids(T):
        out += prefix(c)
    return out


def suffix(T):
    """Return the list of keys: each child subtree left to right, then the root."""
    if T is None:
        return []
    out = []
    for c in _kids(T):
        out += suffix(c)
    return out + [T.key]


def level_order(T):
    """Return the list of keys level by level, left to right."""
    return [n.key for l in _levels(T) for n in l]


def print_level(T, k):
    """Print (one per line) the keys of all nodes at depth k, left to right."""
    if T is None or k < 0:
        return
    if k == 0:
        print(T.key)
        return
    for c in _kids(T):
        print_level(c, k - 1)


def reverse_prefix(T):
    """Return the list of keys: root, then its child subtrees visited right to left."""
    if T is None:
        return []
    out = [T.key]
    for c in reversed(list(_kids(T))):
        out += reverse_prefix(c)
    return out


def leftmost_leaf(T):
    """Return the first leaf met in prefix order (None if T is empty)."""
    if T is None:
        return None
    while T.first_child is not None:
        T = T.first_child
    return T


def rightmost_leaf(T):
    """Return the last leaf met in prefix order (None if T is empty)."""
    if T is None:
        return None
    if T.first_child is None:
        return T
    last = T.first_child
    while last.next_sibling is not None:
        last = last.next_sibling
    return rightmost_leaf(last)


# ===========================================================================
# 4. AGGREGATIONS AND STATISTICS   (keys are assumed to be numbers)
# ===========================================================================

def sum_keys(T):
    """Return the sum of all keys (0 if empty)."""
    if T is None:
        return 0
    return T.key + sum(sum_keys(c) for c in _kids(T))


def min_key(T):
    """Return the minimum key (None if empty)."""
    if T is None:
        return None
    best = T.key
    for c in _kids(T):
        m = min_key(c)
        if m < best:
            best = m
    return best


def max_key(T):
    """Return the maximum key (None if empty)."""
    if T is None:
        return None
    best = T.key
    for c in _kids(T):
        m = max_key(c)
        if m > best:
            best = m
    return best


def _sum_count(T):
    """Return the pair (sum of keys, number of nodes)."""
    if T is None:
        return (0, 0)
    s, n = T.key, 1
    for c in _kids(T):
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
    if T.first_child is None:
        return T.key
    return sum(sum_leaves(c) for c in _kids(T))


def count_even(T):
    """Return the number of nodes with an even key."""
    if T is None:
        return 0
    return (T.key % 2 == 0) + sum(count_even(c) for c in _kids(T))


def count_greater(T, x):
    """Return the number of nodes whose key is strictly greater than x."""
    if T is None:
        return 0
    return (T.key > x) + sum(count_greater(c, x) for c in _kids(T))


def max_subtree_size(T):
    """Return the size of the largest child subtree of the root (0 if no child)."""
    if T is None:
        return 0
    return max((size(c) for c in _kids(T)), default=0)


def sum_level(T, k):
    """Return the sum of the keys at depth k."""
    if T is None or k < 0:
        return 0
    if k == 0:
        return T.key
    return sum(sum_level(c, k - 1) for c in _kids(T))


def average_subtree_size(T):
    """Return the average size of the root's child subtrees (None if no child)."""
    n = count_children(T)
    if n == 0:
        return None
    return sum(size(c) for c in _kids(T)) / n


# ===========================================================================
# 5. SEARCHING AND LOCATING NODES
# ===========================================================================

def contains(T, x):
    """Return True if some node has key x."""
    if T is None:
        return False
    return T.key == x or any(contains(c, x) for c in _kids(T))


def find_node(T, x):
    """Return the first node (prefix order) with key x, None if absent."""
    if T is None:
        return None
    if T.key == x:
        return T
    for c in _kids(T):
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
    for c in _kids(T):
        r = find_min_node(c)
        if r.key < best.key:
            best = r
    return best


def find_max_node(T):
    """Return a node holding the maximum key (first in prefix order), None if empty."""
    if T is None:
        return None
    best = T
    for c in _kids(T):
        r = find_max_node(c)
        if r.key > best.key:
            best = r
    return best


def first_matching(T, p):
    """Return the first node (prefix order) whose key satisfies predicate p, None if none."""
    if T is None:
        return None
    if p(T.key):
        return T
    for c in _kids(T):
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
    for c in _kids(T):
        p = path_to(c, x)
        if p is not None:
            return [T.key] + p
    return None


def parent_of(T, x):
    """Return the parent node of the first node with key x (None if x is the root
    or absent). No parent pointer exists: the parent is found while descending."""
    if T is None:
        return None
    for c in _kids(T):
        if c.key == x:
            return T
    for c in _kids(T):
        r = parent_of(c, x)
        if r is not None:
            return r
    return None


def are_siblings(T, x, y):
    """Return True if two distinct nodes with keys x and y share the same parent."""
    if T is None:
        return False
    kids = list(_kids(T))
    for i in range(len(kids)):
        for j in range(len(kids)):
            if i != j and kids[i].key == x and kids[j].key == y:
                return True
    return any(are_siblings(c, x, y) for c in kids)


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
    return T.key > 0 and all(all_positive(c) for c in _kids(T))


def all_leaves_even(T):
    """Return True if every leaf has an even key."""
    if T is None:
        return True
    if T.first_child is None:
        return T.key % 2 == 0
    return all(all_leaves_even(c) for c in _kids(T))


def all_arity_at_most(T, k):
    """Return True if every node has at most k children."""
    if T is None:
        return True
    return count_children(T) <= k and all(all_arity_at_most(c, k) for c in _kids(T))


def all_arity_equal(T, k):
    """Return True if every internal node has EXACTLY k children."""
    if T is None or T.first_child is None:
        return True
    return count_children(T) == k and all(all_arity_equal(c, k) for c in _kids(T))


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
    return all(c.first_child is None for c in _kids(T))


def _leaf_depths(T, d=0):
    if T is None:
        return []
    if T.first_child is None:
        return [d]
    return [x for c in _kids(T) for x in _leaf_depths(c, d + 1)]


def all_leaves_same_depth(T):
    """Return True if all leaves are at the same depth."""
    return len(set(_leaf_depths(T))) <= 1


def _arities(T):
    if T is None or T.first_child is None:
        return []
    return [count_children(T)] + [a for c in _kids(T) for a in _arities(c)]


def is_perfect(T):
    """Perfect-tree definition used here: all internal nodes have the SAME number
    of children and all leaves are at the same depth."""
    return len(set(_arities(T))) <= 1 and all_leaves_same_depth(T)


def has_unary_node(T):
    """Return True if some node has exactly one child."""
    if T is None:
        return False
    return count_children(T) == 1 or any(has_unary_node(c) for c in _kids(T))


def every_child_larger(T):
    """Return True if every child key is strictly greater than its parent's key."""
    if T is None:
        return True
    return all(c.key > T.key and every_child_larger(c) for c in _kids(T))


def _morechildren(T, parent_arity):
    if T is None or T.first_child is None:
        return True
    n = count_children(T)
    if parent_arity is not None and n <= parent_arity:
        return False
    return all(_morechildren(c, n) for c in _kids(T))


def morechildren(T):
    """Return True if every non-root internal node has strictly more children
    than its parent."""
    return _morechildren(T, None)


def average_subtrees(T):
    """Exact condition used here: for every internal node N and for each child c
    of N, the average of ALL keys in the subtree rooted at c is greater than or
    equal to key(N)."""
    if T is None:
        return True
    for c in _kids(T):
        s, n = _sum_count(c)
        if s / n < T.key or not average_subtrees(c):
            return False
    return True


# ===========================================================================
# 7. RELATIONSHIPS BETWEEN SUBTREES
# ===========================================================================

def same_tree(T, U):
    """Return True if T and U (two roots) have identical structure AND keys."""
    if T is None or U is None:
        return T is None and U is None
    if T.key != U.key:
        return False
    a, b = T.first_child, U.first_child
    while a is not None and b is not None:
        if not same_tree(a, b):
            return False
        a, b = a.next_sibling, b.next_sibling
    return a is None and b is None


def same_structure(T, U):
    """Return True if T and U have the same shape, ignoring keys."""
    if T is None or U is None:
        return T is None and U is None
    a, b = T.first_child, U.first_child
    while a is not None and b is not None:
        if not same_structure(a, b):
            return False
        a, b = a.next_sibling, b.next_sibling
    return a is None and b is None


def symmetric(T, U):
    """Return True if U is the mirror image of T (same keys, children reversed everywhere)."""
    if T is None or U is None:
        return T is None and U is None
    if T.key != U.key:
        return False
    ka, kb = list(_kids(T)), list(_kids(U))
    if len(ka) != len(kb):
        return False
    return all(symmetric(a, b) for a, b in zip(ka, reversed(kb)))


def is_symmetric(T):
    """Return True if T is its own mirror image."""
    return symmetric(T, T)


def is_subtree(T, U):
    """Return True if U (a root, keys included) occurs as a complete subtree of T.
    The empty tree is a subtree of every tree."""
    if U is None:
        return True
    if T is None:
        return False
    return same_tree(T, U) or any(is_subtree(c, U) for c in _kids(T))


def count_equal_subtrees(T):
    """Return the number of unordered pairs of the root's children whose
    subtrees have the same structure."""
    if T is None:
        return 0
    kids = list(_kids(T))
    return sum(1 for i in range(len(kids)) for j in range(i + 1, len(kids))
               if same_structure(kids[i], kids[j]))


def largest_subtree(T):
    """Return the child of the root with the greatest size (first on ties), None if no child."""
    if T is None or T.first_child is None:
        return None
    best, best_size = None, -1
    for c in _kids(T):
        s = size(c)
        if s > best_size:
            best, best_size = c, s
    return best


def all_subtrees_satisfy(T, p):
    """Return True if predicate p (taking a root node) holds for EVERY subtree of T,
    including T itself. Note: p must only look at the subtree of its argument,
    not at its next_sibling."""
    if T is None:
        return True
    return p(T) and all(all_subtrees_satisfy(c, p) for c in _kids(T))


def are_all_children_equal(T):
    """Return True if all direct child subtrees of the root are identical (keys included)."""
    if T is None or T.first_child is None:
        return True
    first = T.first_child
    return all(same_tree(first, c) for c in _kids(T))


# ===========================================================================
# 8. TRANSFORMATIONS   (return a NEW tree; the original is never modified)
# ===========================================================================

def copy_tree(T):
    """Return a deep copy of T."""
    if T is None:
        return None
    return _build(T.key, [copy_tree(c) for c in _kids(T)])


def mirror(T):
    """Return a copy of T where the children order is reversed at every node."""
    if T is None:
        return None
    return _build(T.key, [mirror(c) for c in reversed(list(_kids(T)))])


def map_tree(T, f):
    """Return a copy of T where every key k is replaced by f(k)."""
    if T is None:
        return None
    return _build(f(T.key), [map_tree(c, f) for c in _kids(T)])


def increment_keys(T):
    """Return a copy of T where every key is increased by one."""
    return map_tree(T, lambda k: k + 1)


def replace_key(T, x, y):
    """Return a copy of T where every key equal to x becomes y."""
    return map_tree(T, lambda k: y if k == x else k)


def remove_leaves(T):
    """Return a copy of T without its leaves. If T is a single leaf, the result is None."""
    if T is None or T.first_child is None:
        return None
    kept = [remove_leaves(c) for c in _kids(T)]
    return _build(T.key, [c for c in kept if c is not None])


def prune(T, k):
    """Return a copy of T where all nodes at depth k (and their subtrees) are removed.
    prune(T, 0) is None."""
    if T is None or k <= 0:
        return None
    kept = [prune(c, k - 1) for c in _kids(T)]
    return _build(T.key, [c for c in kept if c is not None])


def filter_tree(T, p):
    """Return a copy keeping a node only if its key satisfies p AND its parent was kept.
    A node failing p is removed together with its whole subtree.
    Returns None if the root fails p."""
    if T is None or not p(T.key):
        return None
    kept = [filter_tree(c, p) for c in _kids(T)]
    return _build(T.key, [c for c in kept if c is not None])


# ===========================================================================
# 9. CONVERSIONS AND LINEAR NOTATION
# ===========================================================================

def to_classical(T):
    """Convert a first-child/next-sibling tree into a classical tree (ClassicalNode)."""
    if T is None:
        return None
    return ClassicalNode(T.key, [to_classical(c) for c in _kids(T)])


def from_classical(C):
    """Convert a classical tree (ClassicalNode) into a first-child/next-sibling tree."""
    if C is None:
        return None
    return _build(C.key, [from_classical(c) for c in C.children])


def to_linear(T):
    """Return the parenthesized notation, e.g. 1(2,3(4)). Empty tree -> ''."""
    if T is None:
        return ""
    if T.first_child is None:
        return str(T.key)
    return str(T.key) + "(" + ",".join(to_linear(c) for c in _kids(T)) + ")"


def from_linear(s):
    """Build a first-child/next-sibling tree from notation like '1(2,3(4))'.
    Keys are read as int when possible, otherwise kept as strings. '' -> None."""
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
        kids = []
        if j < len(s) and s[j] == "(":
            j += 1
            while True:
                kid, j = parse(j)
                kids.append(kid)
                if s[j] == ",":
                    j += 1
                else:
                    break
            j += 1  # skip ')'
        return _build(key, kids), j

    tree, _ = parse(0)
    return tree


def serialize(T):
    """Return a flat list [key, nb_children, key, nb_children, ...] in prefix order.
    Empty tree -> []."""
    if T is None:
        return []
    out = [T.key, count_children(T)]
    for c in _kids(T):
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
        return _build(key, [build() for _ in range(n)])

    return build()


def same_tree_representations(T, C):
    """T is a first-child/next-sibling tree, C is a classical tree (ClassicalNode).
    Return True if they represent the same tree (same keys, same structure,
    same child order)."""
    if T is None or C is None:
        return T is None and C is None
    if T.key != C.key or count_children(T) != C.nb_children:
        return False
    return all(same_tree_representations(a, b) for a, b in zip(_kids(T), C.children))


# ===========================================================================
# 10. EXTRA: SIBLING CHAINS AND LINK MANIPULATION
#     Here T is a node of a sibling chain (it may have next_sibling != None).
# ===========================================================================

def size_chain(T):
    """Return the number of nodes of T, of its descendants AND of all following
    siblings (with their descendants). On a root (no sibling) this is size(T).
        return 1 + size_chain(T.first_child) + size_chain(T.next_sibling)"""
    if T is None:
        return 0
    return 1 + size_chain(T.first_child) + size_chain(T.next_sibling)


def height_chain(T):
    """Return the maximum height among T and all its following siblings
    (-1 if T is None). On a root this is height(T)."""
    if T is None:
        return -1
    return max(1 + height_chain(T.first_child), height_chain(T.next_sibling))


def last_sibling(T):
    """Return the last node of the sibling chain starting at T (None if T is None)."""
    if T is None:
        return None
    while T.next_sibling is not None:
        T = T.next_sibling
    return T


def nth_child(T, n):
    """Return the n-th child (0-based) of the root T, None if it does not exist."""
    if T is None or n < 0:
        return None
    c = T.first_child
    while c is not None and n > 0:
        c = c.next_sibling
        n -= 1
    return c


def add_child_first(T, U):
    """MODIFY T: make the tree U (a root, U.next_sibling is None) the new FIRST
    child of T. Return T."""
    U.next_sibling = T.first_child
    T.first_child = U
    return T


def add_child_last(T, U):
    """MODIFY T: make the tree U (a root, U.next_sibling is None) the new LAST
    child of T. Return T."""
    if T.first_child is None:
        T.first_child = U
    else:
        last_sibling(T.first_child).next_sibling = U
    return T


def remove_first_child(T):
    """MODIFY T: detach the first child of T (its next siblings stay children
    of T). Return the detached subtree (with next_sibling reset to None),
    or None if T has no child."""
    c = T.first_child
    if c is None:
        return None
    T.first_child = c.next_sibling
    c.next_sibling = None
    return c


# ---------------------------------------------------------------------------
# Quick self-test:  python general_trees_fcns.py
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    #           1
    #         / | \
    #        2  3  4
    #       / \     |
    #      5   6    7
    T = from_linear("1(2(5,6),3,4(7))")

    assert T.next_sibling is None and T.first_child.key == 2
    assert T.first_child.next_sibling.key == 3
    assert size(T) == 7 and count_leaves(T) == 4 and count_internal(T) == 3
    assert count_children(T) == 3 and count_siblings(T.first_child) == 3
    assert height(T) == 2 and max_arity(T) == 3 and min_arity(T) == 1
    assert average_arity(T) == 2
    assert count_nodes_at_depth(T, 2) == 3 and width(T) == 3 and widest_level(T) == 1
    assert prefix(T) == [1, 2, 5, 6, 3, 4, 7]
    assert suffix(T) == [5, 6, 2, 3, 7, 4, 1]
    assert level_order(T) == [1, 2, 3, 4, 5, 6, 7]
    assert reverse_prefix(T) == [1, 4, 7, 3, 2, 6, 5]
    assert leftmost_leaf(T).key == 5 and rightmost_leaf(T).key == 7
    assert sum_keys(T) == 28 and max_key(T) == 7 and min_key(T) == 1
    assert sum_leaves(T) == 5 + 6 + 3 + 7 and count_even(T) == 3
    assert max_subtree_size(T) == 3 and sum_level(T, 1) == 9
    assert path_to(T, 6) == [1, 2, 6] and depth(T, 7) == 2
    assert parent_of(T, 5).key == 2 and parent_of(T, 1) is None
    assert are_siblings(T, 5, 6) and not are_siblings(T, 5, 7)
    assert nodes_after(T, 3) == [4, 7]
    assert not is_chain(T) and is_n_ary(T, 3) and not is_perfect(T)
    assert is_perfect(from_linear("1(2(4,5),3(6,7))"))
    assert not morechildren(T) and every_child_larger(T) and all_positive(T)
    assert average_subtrees(T)
    assert same_tree(T, copy_tree(T)) and same_structure(T, increment_keys(T))
    assert not same_tree(T, increment_keys(T))
    assert symmetric(T, mirror(T)) and not is_symmetric(T)
    assert is_symmetric(from_linear("1(2,3,2)"))
    assert is_subtree(T, from_linear("4(7)")) and not is_subtree(T, from_linear("4(8)"))
    assert count_equal_subtrees(from_linear("1(2,3,4(5))")) == 1
    assert largest_subtree(T).key == 2 and are_all_children_equal(from_linear("1(2,2,2)"))
    assert to_linear(remove_leaves(T)) == "1(2,4)"
    assert to_linear(prune(T, 2)) == "1(2,3,4)"
    assert to_linear(filter_tree(T, lambda k: k != 2)) == "1(3,4(7))"
    assert to_linear(mirror(T)) == "1(4(7),3,2(6,5))"
    assert to_linear(T) == "1(2(5,6),3,4(7))"          # originals untouched
    C = to_classical(T)
    assert same_tree_representations(T, C) and same_tree(T, from_classical(C))
    assert same_tree(T, deserialize(serialize(T)))
    assert size_chain(T) == 7 and size_chain(T.first_child) == 6
    assert height_chain(T.first_child) == 1
    assert last_sibling(T.first_child).key == 4 and nth_child(T, 1).key == 3
    U = from_linear("1(2)")
    add_child_last(U, node(3))
    add_child_first(U, node(0))
    assert to_linear(U) == "1(0,2,3)"
    assert remove_first_child(U).key == 0 and to_linear(U) == "1(2,3)"
    print("All tests passed.")
