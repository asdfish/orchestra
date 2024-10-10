# orchestra
c string library

## Building
~~~sh
git clone https://github.com/asdfish/orchestra --depth=1
cd orchestra
make
~~~
There are preprocessor flags that you can change before you compile, see [documentation](DOCUMENTATION.md) for more details.

## Usage
~~~sh
cc -Lorchestra -lorchestra -Iorchestra/include
~~~
If orchestra is cloned to a different directory, change -L and -I to the location of the repository.

## Documentation
See [DOCUMENTATION.md](DOCUMENTATION.md).
