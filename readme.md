<h1 align="center">
	<a href="https://github.com/KeyC0de/BuilderPattern">Builder Pattern</a>
</h1>
<hr>


An introduction to the important Builder design pattern.
There is a nice example to make you go from Zero-to-Hero fast with this pattern!

The Builder pattern is designed to provide a flexible solution to various object creation problems in oop. We intend to separate the construction of a complex object from its representation.

**Advantages**
It provides control over the individual steps in the object construction process st we can better customize object representation.
The benefits of the builder design pattern really shine when we have big, complicated classes termed 'Product' classes.


**Disadvantages**
Disadvantages are it requires a separate Builder class for each type of such complex object and it makes dependency injection harder to work with since introducing many dependencies can get things out of hand. Also it increases code size and almost doubles the amount of memory required since almost all variables (except possibly those with some default values and constants) have to be duplicated in the nested Builder class.

**Design**

- create your target big/complex class you want to generate objects, aka the Product class
- create a nested class called `Builder`.
- The `Builder` class contains:
	- the state data required to build the object, which means many of the data contained in the outer/target class (if not more for data needed by other interacting classes with the Product class)
	- setter functions for each data member of the Builder class, which are called to customize the properties of our Product object (or make the data a public struct). They all return a reference to Builder& such that we can chain multiple of them nice and easy
	- a `create` method returning the Object created in that return statement back to the caller


# Usage

Create your `Builder` object like so:

```
auto myProduct = Product::Builder{}
	.setX(1)
	.setY(2)
	.setZ(3)
	.setName("Key")
	.setColor("Black")
	.set...()
	. ...
	.create();
```

Notice that each getter/setter returns a reference to the 'Builder' so we can use function chaining to our advantage. The `create()` function goes last and takes no arguments.

I used Windows 8.1 x86_64, Visual Studio 2017, C++17 to build the project.


# Contribute

Please submit any bugs you find through GitHub repository 'Issues' page with details describing how to replicate the problem. If you liked it or you learned something new give it a star, clone it, contribute to it whatever. Enjoy.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.


# Contact

email: *nik.lazkey@gmail.com*</br>
website: *www.keyc0de.net*

