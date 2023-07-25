# initial-kv

this is a simple persistent key-value store
demonstrating basics of c and
systems programming.

the full list of commands which the kv store supports are:
- *put*: the format is `p,key,value`, where `key` is an integer, and
`value` an arbitrary string (without commas in it).
- *get*: the format is `g,key`, where `key` is an integer. if the key
is present, the system should print out the key, followed by a comma,
followed by the value, followed by a newline (`\n`). if not present,
print an error message on a line by itself, of the form `k not found`
where `k` is the actual value of the key, i.e., some integer. 
- *delete*: the format is `d,key`, which either deletes the relevant
key-value pair (and prints nothing), or fails to do so (and prints
`k not found` where `k` is the actual value of the key, i.e., some
integer).
- *clear*: the format is `c`. this command simply removes all
key-value pairs from the database.
- *all*: the format is `a`. this command prints out all key-value
pairs in the database, in any order, with one key-value pair per line,
each key and value separated by a comma.

### EXample
```sh
prompt> ./kv 
prompt> ./kv p,10,remzi
prompt> ./kv p,20,andrea p,40,someotherperson
```
