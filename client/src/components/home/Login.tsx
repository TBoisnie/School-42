import { useMemo } from 'react';
import { Container, Stack } from 'react-bootstrap';
import Header from '../common/Header';
import LoginForm from './login/Login';
import Omniauth from './omniauth/Omniauth';
import Register from './register/Register';
import { useTranslation } from 'react-i18next';

const Login: React.FC = () => {

  // 5. useCustom
  const { t } = useTranslation();

  // 6. useCallback / useMemo
  const header = useMemo(() => t('login.header.header'), [t]);
  const paragraph = useMemo(() => t('login.header.paragraph'), [t]);

  return (
    <Container className="align-self-center">
      <Stack direction="vertical" gap={3}>
        <Header header={header} paragraph={paragraph} />
        <LoginForm />
        <Omniauth />
        <Register />
      </Stack>
    </Container>
  );
};

export default Login;
