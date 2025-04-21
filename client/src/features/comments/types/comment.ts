
export type Comment =
{
	id: number;
	content: string;
	author: {
		id: number;
		username: string;
	};
};
