---
layout: post
title: Bit Level Hacking
date: 2022-02-06 12:31:00
description: Fast inverse square root
tags: code
categories: story
---

My website wouldn't be complete if it didn't mention Fast InvSqrt().

This function is what made me interested in software engineering.

In short, this is how lighting and reflection calculations are done in the 1999 video game *[Quake III Arena](https://youtu.be/cyCgMQvG_rc?t=217)*.

You can read more [on Wikipedia](https://en.wikipedia.org/wiki/Fast_inverse_square_root), or listen [to this YouTube video](https://www.youtube.com/watch?v=p8u_k2LIZyo) for something more digestable.

***

> Fast inverse square root, sometimes referred to as Fast InvSqrt() or by the hexadecimal constant <code>0x5F3759DF</code>, is an algorithm that estimates the reciprocal (or multiplicative inverse) of the square root of a 32-bit floating-point number <code>x</code> in IEEE 754 floating-point format.

***

{% highlight c linenos %}

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

{% endhighlight %}

***