pipeline {
  agent none
  stages {
    stage('python version') {
      agent { dockerfile { filename 'Dockerfile' }}
      steps {
        sh 'python --version'
        SconsCommand('--version')
      }
    }
    
    
    stage('build Simulations') {
      agent { dockerfile { filename 'Dockerfile' }}
      steps { SconsCommand('Simulations') }
    }
    stage('build Simulations debug') {
      agent { dockerfile { filename 'Dockerfile' }}
      steps { SconsCommand('--debug_build Simulations') }
    }
  }
}

def SconsCommand(cmd)
{
    sh 'scons ' + cmd
}
