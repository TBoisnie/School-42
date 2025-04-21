import React, { createContext, useContext, useState, useEffect, useCallback } from 'react';

interface AuthContextType {
  isAuthenticated: boolean;
  setIsAuthenticated: (isAuthenticated: boolean) => void;
}

// Create the authentication context
export const AuthContext = createContext<AuthContextType | undefined>(undefined);

// Authentication context provider
export const AuthProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [isAuthenticated, setIsAuthenticated] = useState<boolean>(false);

  const checkAuthentication = useCallback(() => {
    const cookies = document.cookie.split(';').map(cookie => cookie.trim());
    let loginCookie = cookies.find(cookie => cookie.startsWith('login='))?.split('=')[1];
    if (loginCookie === undefined) {
      document.cookie = 'login=false; path=/';
      loginCookie = 'false';
    }
    setIsAuthenticated(loginCookie === 'true');
  }, []);

  useEffect(() => {
    checkAuthentication();
  }, [checkAuthentication]);

  return (
    <AuthContext.Provider value={{ isAuthenticated, setIsAuthenticated }}>
      {children}
    </AuthContext.Provider>
  );
};

// Hook to use the authentication context
export const useAuth = () => {
  const context = useContext(AuthContext);
  if (context === undefined) {
    throw new Error('useAuth must be used within an AuthProvider');
  }
  return context;
};