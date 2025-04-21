const email = (email: string): string | null => {
    const emailRegex = /^(?=.{6,255}$)([^@]+@[^@]+\.[^@\s]{2,})$/u;
    if (!emailRegex.test(email)) {
        return "The email must be valid according to international standards.";
    }
    return null;
};

const password = (password: string): string | null => {
    const requirements = [
        { regex: /^[\p{L}\p{N}\p{P}\p{S}]{8,64}$/u, message: "8 characters" },
        { regex: /[\p{Ll}]/u, message: "1 lowercase letter" },
        { regex: /[\p{Lu}]/u, message: "1 uppercase letter" },
        { regex: /[\p{N}]/u, message: "1 digit" },
        { regex: /[\p{P}\p{S}]/u, message: "1 special character" }
        
    ];

    const missingRequirements = requirements
        .filter(req => !req.regex.test(password))
        .map(req => req.message);

    if (missingRequirements.length > 0) {
        return `The password must contain at least ${missingRequirements.join(", ")}`;
    }

    return null;
};

const username = (username: string): string | null => {
    const usernameRegex = /^[\p{L}\p{N}]{4,20}$/u;
    if (!usernameRegex.test(username)) {
        return "The username must be between 4 and 20 characters, only letters and digits.";
    }
    return null;
};

const firstName = (firstName: string): string | null => {
    const firstNameRegex = /^[\p{L}]{2,50}$/u;
    if (!firstNameRegex.test(firstName)) {
        return "The first name must be between 2 and 50 characters, only letters.";
    }
    return null;
};

const lastName = (lastName: string): string | null => {
    const lastNameRegex = /^[\p{L}]{2,50}$/u;
    if (!lastNameRegex.test(lastName)) {
        return "The last name must be between 2 and 50 characters, only letters.";
    }
    return null;
};

export { email, password, username, firstName, lastName };
