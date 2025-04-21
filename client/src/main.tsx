import 'bootstrap/dist/css/bootstrap.min.css';
import './index.css';

import { createRoot } from 'react-dom/client';
import { BrowserRouter, BrowserRouter as Router } from 'react-router-dom';

import { AuthProvider } from './components/contexts/AuthContext.tsx';
import App from './App.tsx';
import { I18nextProvider } from 'react-i18next';
import i18n from './utilities/Translation.tsx';
import { ModalProvider } from './components/contexts/ModalContext.tsx';

// Component structure order:
// 1. useState: to manage local component state.
// 2. useReducer: for more complex state management, if necessary.
// 3. useContext: to access context data.
// 4. useRef: for persistent references.
// 5. useCustom: to include imported custom hooks (like useNavigate, useTranslate).
// 6. useCallback / useMemo: to optimize memorized functions and values.
// 7. Event handlers: for functions passed as props (like onClick, onChange).
// 8. useEffect: to execute side effects after rendering.

createRoot(document.getElementById('root')!).render(
    <AuthProvider>
      <I18nextProvider i18n={i18n}>
        <ModalProvider >
        <Router future={{ v7_startTransition: true, v7_relativeSplatPath: true }}>

            <App />
            </Router>

        </ModalProvider>
      </I18nextProvider>
    </AuthProvider>

);
