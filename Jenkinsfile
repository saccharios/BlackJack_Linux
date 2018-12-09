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
    
    stage('Sim'){
      agent { dockerfile { filename 'Dockerfile' }}
      stages{
        stage('build Simulations') {
          steps { SconsCommand('Simulations') }
        }
        stage('build Simulations debug') {
          steps { SconsCommand('--debug_build Simulations') }
        }
      }
    }
  }
}

def SconsCommand(cmd)
{
    sh 'scons ' + cmd
}
