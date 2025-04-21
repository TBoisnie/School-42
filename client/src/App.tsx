import { Container, Row } from 'react-bootstrap';
import AppRoutes from './AppRoutes';
import './App.css';
import Navigation from './components/navigation/Navigation';
import { useCallback } from 'react';

function App() {

  // 6. useMemo / useCallback
  const handleHeader = useCallback(() => {
    return (
      <header>
          <Navigation />
      </header>
    );
  }, []);

  const handleMain = useCallback(() => {
    return (
      <main
        className="container shadow-lg text-white h-100 px-0"
        style={{
          paddingTop: '3.5rem',
          paddingBottom: '7.0rem',
        }}
        >
          <AppRoutes />
      </main>
    );
  }, []);

  const handleFooter = useCallback(() => {
    return (
      <footer className="position-fixed text-white text-center px-2"
        style={{
          borderTopLeftRadius: '0.25rem',
          right: 0,
          bottom: 0,
        }}
      >
        2024 hypertube by lparis & tboisnie
      </footer>
    );
  }, []);

  return (
    <div className="h-100 bg-dark">
      {handleHeader()}
      {handleMain()}
      {handleFooter()}
      </div>
  );
}

export default App;
