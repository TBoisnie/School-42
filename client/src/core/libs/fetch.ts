
export abstract class Fetch
{

	private static readonly BASE_URL = 'https://localhost:5173/api';

	public static async request(
		path: string,
		options?: RequestInit,
	)
		: Promise< Response >
	{
		return fetch(`${ Fetch.BASE_URL }${ path }`, options);
	}

	public static async get(
		path: string,
		options?: Omit< RequestInit, 'method' >
	)
		: Promise< Response >
	{
		return Fetch.request(path, { ...options, method: 'GET' });
	}

	public static async post(
		path: string,
		options?: Omit< RequestInit, 'method' >
	)
		: Promise< Response >
	{
		return Fetch.request( path, { ...options, method: 'POST' } );
	}

	public static async patch(
		path: string,
		options?: Omit< RequestInit, 'method' >
	)
		: Promise< Response >
	{
		return Fetch.request( path, { ...options, method: 'PATCH' } );
	}

	public static async delete(
		path: string,
		options?: Omit< RequestInit, 'method' >
	)
		: Promise< Response >
	{
		return Fetch.request( path, { ...options, method: 'DELETE' } );
	}

};
