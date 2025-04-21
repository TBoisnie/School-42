import { Routes, Route, Navigate } from 'react-router-dom';
import Register from './components/register/Register';
import Reset from './components/reset/Reset';
import Confirm from './components/confirm/Confirm';
import Profile from './components/profile/Profile';
import Users from './components/users/Users';
import UserDetail from './components/users/detail/Detail';
import { useAuth } from './components/contexts/AuthContext';
import Response from './components/oauth/Response';
import { Component as MovieBrowserPage } from './pages/movies/browse';
import { Component as MoviePlayPage } from './pages/movies/play';
import { Component as LoginPage } from './pages/auth/login';
import { Component as NotFoundPage } from './pages/error/not-found';
import { Component as HomePage } from './pages/app/home';
import AuthLayout from './components/AuthLayout';

const AppRoutes: React.FC = () => {

  const { isAuthenticated } = useAuth();

  return (
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route element={<AuthLayout /> }>
          <Route path="/auth/login" element={isAuthenticated ? <Navigate to={'/'} /> : <LoginPage />} />
          <Route path="/auth/profile" element={isAuthenticated ? <Profile /> : <Navigate to={'/auth/login'} /> } />
          <Route path="/auth/register" element={isAuthenticated ? <Navigate to={'/'} /> : <Register />} />
          <Route path="/auth/reset" element={isAuthenticated ? <Navigate to={'/'} /> : <Reset />} />
          <Route path="/auth/confirm" element={isAuthenticated ? <Navigate to={'/'} /> : <Confirm />} />
          <Route path="/oauth/42/callback" element={<Response />} />
          <Route path="/oauth/google/callback" element={<Response />} />
          <Route path="/oauth/github/callback" element={<Response />} />
          <Route path="/users" element={isAuthenticated ? <Users /> : <Navigate to={'/auth/login'} />} />
          <Route path="/users/:id" element={isAuthenticated ? <UserDetail /> : <Navigate to={'/auth/login'} />} />
        </Route>
        <Route path="/movies" element={isAuthenticated ? <MovieBrowserPage /> : <Navigate to={'/auth/login'} /> } />
        <Route path="/movies/:imdb_id" element={isAuthenticated ? <MoviePlayPage /> : <Navigate to={'/auth/login'} /> } />
        <Route path="*" element={<NotFoundPage />} />
      </Routes>
  );
};

export default AppRoutes;
