function Check_Equals(_str1, _str2)
{
	if (_str1.length !== _str2.length) return 0;
	for (let i = 0; i < _str1.length; i++)
	{
		if (_str1[i] !== _str2[i]) return 0;
	}
	return 1;
}
function Pow(a,b)
{
	return Math.pow(a,b);
}
function max(x, y)
{
	if(x >= y)
	{
		return x;
	}
	else
	{
		return y;
	}
	return 0;
}
function strffunction(x)
{
	x = "dsasd";
	return "";
}
function qq(x, y)
{
	if(x >= y)
	{
		return x;
	}
	else
	{
		return y;
	}
	return 0;
}
function qwerty(x, y)
{
	if(x === y)
	{
		return 11;
	}
	else
	{
		return 22;
	}
	return 0;
}
function zxcv(x, y)
{
	if(x !== y)
	{
		return 11;
	}
	else
	{
		return 22;
	}
	return 0;
}
function main()
{
	let a = 0;
	let b = 0;
	let c = 0;
	a = 3;
	b = 4;
	if(a > b)
	{
		c = 100;
	}
	else
	{
		c = 200;
	}
	console.log(c);
	return 0;
}

//==============================================
main()
